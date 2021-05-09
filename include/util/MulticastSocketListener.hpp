#ifndef MULTICAST_SOCKET_LISTENER_HPP_
#define MULTICAST_SOCKET_LISTENER_HPP_

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace util {

template <class Data> class MulticastSocketListener {
public:
  MulticastSocketListener(const char *group, int port) {
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
      throw std::runtime_error("Socket could not open!");
    }

    fcntl(socket_fd, F_SETFL, O_NONBLOCK);

    u_int yes = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&yes,
                   sizeof(yes)) < 0) {
      throw std::runtime_error("Reusing ADDR is failed!");
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
      throw std::runtime_error("Socket binding is failed!");
    }

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(group);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    // Request join multicast group from kernel.
    if (setsockopt(socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq,
                   sizeof(mreq)) < 0) {
      throw std::runtime_error("Socket options could not be set!");
    }
  }

  int next(Data &data) const noexcept {
    int nbytes;
    do {
      nbytes = recv(socket_fd, &data, sizeof(Data), 0);
      if (nbytes == -1) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
          return 1;
        } else if (errno != EINTR) {
          return -1;
        }
      } else if (nbytes == sizeof(Data)) {
        return 0;
      } else if (nbytes == 0) {
        fprintf(stderr, "Stream socket peer may be closed!\n");
        return -2;
      }
    } while (errno == EINTR);

    return -1; /* if number of bytes bigger than 0 but not equal to expected */
  }

private:
  int socket_fd;
};

} // namespace util

#endif // MULTICAST_SOCKET_LISTENER_HPP_

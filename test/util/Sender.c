#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

char group[64] = "234.5.5.5";
int port = 10200;

typedef enum mock_game { MOCK_ONE } mock_game_t;

typedef struct mock_info {
  int size;
  char path[256];
} mock_info_t;

typedef struct packet {
  uint16_t ball_position_x;
  uint16_t ball_position_y;
  uint16_t arm_snt_position;
  uint16_t arm_gk_position;
  uint16_t score_human;
  uint16_t score_robot;
} packet_t;

void create_raw_data(uint16_t *raw_data, packet_t *packet);

mock_info_t get_mock_info(mock_game_t game) {

  mock_info_t info;

  switch (game) {
  case MOCK_ONE:
    strcpy(info.path, "../data/mock-game1");
    info.size = 1646;
    break;
  default:
    fprintf(stderr, "Back mock_game_t\n");
    info.size = -1;
    break;
  }

  return info;
}

packet_t *make_packet(mock_game_t game) {
  packet_t *t;
  switch (game) {
  case MOCK_ONE:
    return (packet_t *)malloc(get_mock_info(game).size * sizeof(packet_t));
  default:
    fprintf(stderr, "Bad mock_game_t\n");
    return NULL;
  }
}

packet_t *make_data(mock_game_t game) {

  char *line = NULL;
  int lc = 0;
  int packets_size = 0;
  packet_t *packets = make_packet(game);

  if (packets == NULL) {
    return NULL;
  }

  FILE *fp = fopen(get_mock_info(game).path, "r");
  if (fp == NULL) {
    fprintf(stderr, "Mock data file: %d could not open: %s\n", game,
            strerror(errno));
    free(packets);
    return NULL;
  }

  size_t llen;

  while (getline(&line, &llen, fp) != -1) {
    ++lc;
    // parse packets_size;
    switch (lc % 3) {
    case 0:
      packets[packets_size].arm_gk_position = strtol(line, NULL, 10);
      packets[packets_size].arm_snt_position =
          packets[packets_size].arm_gk_position;
      ++packets_size;
      break;
    case 1:
      memset(packets + packets_size, 0, sizeof(packet_t));
      packets[packets_size].ball_position_x = strtol(line, NULL, 10);
      break;
    case 2:
      packets[packets_size].ball_position_y = strtol(line, NULL, 10);
      break;
    }
  }

  fclose(fp);
  if (line)
    free(line);

  return packets;
}

int main(int argc, char *argv[]) {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd < 0) {
    perror("socket");
    return 1;
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(group);
  addr.sin_port = htons(port);

  mock_game_t game = MOCK_ONE;
  mock_info_t info = get_mock_info(game);
  packet_t *packets = make_data(game);
  int i = 0;

  while (i < info.size) {
    // Dummy data olustur.
    uint16_t raw_data[6];
    create_raw_data(raw_data, packets + i);
    int nbytes = sendto(fd, &raw_data, sizeof(raw_data), 0,
                        (struct sockaddr *)&addr, sizeof(addr));
    if (nbytes < 0) {
      perror("sendto");
      return 1;
    }
    ++i;

    // 2 hz frequency.
    usleep(500000 / 4);
  }

  return 0;
}

void create_raw_data(uint16_t *raw_data, packet_t *packet) {
  raw_data[0] = packet->ball_position_x;
  raw_data[1] = packet->ball_position_y;
  raw_data[2] = packet->arm_snt_position;
  raw_data[3] = packet->arm_gk_position;
  raw_data[4] = packet->score_human;
  raw_data[5] = packet->score_robot;
}

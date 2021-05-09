#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


uint16_t ball_position_x;
uint16_t ball_position_y;
uint16_t arm_snt_position;
uint16_t arm_gk_position;
uint16_t score_human;
uint16_t score_robot;

/* global degiskenler */
const char group[64] 	= "234.5.5.5";
const int port 			= 10200;

int socket_fd;
struct sockaddr_in addr;
struct ip_mreq mreq;
/* global degiskenler */


/**
* Gelen bytelari structa donusturur.
*/
void parse_data_pckt(const uint16_t* raw_data);

/**
* Oyun bilgisini alir, global degiskenlere yazar.
* @return Veri eksiksiz alinmissa 0 return eder, eksikse -1.
*/
int  get_game_data();

/**
* Globalde belirtilen ip ve port ayarlarina gore baglantiyi baslatir.
*/
int init_connection();

int main(int argc, char *argv[])
{
  	
  	if(-1 == init_connection())
  	{
  		// baglanti ayarlarinda hata..
  		perror("");
  		exit(EXIT_FAILURE);
  	}
    
    while (1)
    {
        if(0 == get_game_data())
        {
        	printf("Ball position x : %d\n", ball_position_x);
            printf("Ball position y : %d\n", ball_position_y);
	        printf("Snt  position   : %d\n", arm_snt_position);
	        printf("Gk   position   : %d\n", arm_gk_position);
	        printf("Human Score     : %d\n", score_human);
	        printf("Robot Score     : %d\n", score_robot);
            printf("----------------------------------------------------\n");
        }
        else
        {
        	// UDP paket  eksik / hatali.
        }
     }

    return 0;
}

int init_connection()
{
	socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        perror("socket");
        return -1;
    }

    u_int yes = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*) &yes, sizeof(yes)) < 0)
    {
       perror("Reusing ADDR failed");
       return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (bind(socket_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        perror("bind");
        return -1;
    }

    mreq.imr_multiaddr.s_addr = inet_addr(group);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    // Request join multicast group from kernel.
    if (setsockopt(socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq, sizeof(mreq)) < 0)
    {
        perror("setsockopt");
        return -1;
    }

    return 0;
}

void parse_data_pckt(const uint16_t* raw_data)
{
	
	ball_position_x     = raw_data[0];
    ball_position_y     = raw_data[1];
    arm_snt_position 	= raw_data[2];
	arm_gk_position 	= raw_data[3];
	score_human 		= raw_data[4];
	score_robot 		= raw_data[5];
}


int get_game_data()
{

	uint16_t data[6];
    int addrlen = sizeof(addr);
    int nbytes = recvfrom(socket_fd,&data ,sizeof(data), 0, (struct sockaddr *) &addr, &addrlen);
    if (nbytes != sizeof(data))
    {
        perror("recvfrom");
        return -1;
    }

    parse_data_pckt(&data);
    return 0;
}

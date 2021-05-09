#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


uint16_t ball_position_x;
uint16_t ball_position_y;
uint16_t arm_snt_position;
uint16_t arm_gk_position;
uint16_t score_human;
uint16_t score_robot;


char group[64] = "234.5.5.5";
int port = 10200;


void create_raw_data(uint16_t* raw_data);

int main(int argc, char *argv[])
{
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

    while (1) 
    {
    	// Dummy data olustur.
        ball_position_x    = 1111;
        ball_position_y    = 2222;
        arm_snt_position =  3333;
        arm_gk_position  = 4444;
        score_human      = 5555;
        score_robot      = 6666;
        uint16_t raw_data[6];
        create_raw_data(raw_data);
        int nbytes = sendto(fd,&raw_data,sizeof(raw_data),0,(struct sockaddr*) &addr, sizeof(addr));
        if (nbytes < 0) {
            perror("sendto");
            return 1;
        }

        // 2 hz frequency.
        usleep(500000);
    }

    return 0;
}

void create_raw_data(uint16_t* raw_data)
{
	raw_data[0] = ball_position_x;
    raw_data[1] = ball_position_y;
	raw_data[2] = arm_snt_position ;
	raw_data[3] = arm_gk_position ;
	raw_data[4] = score_human;
	raw_data[5] = score_robot;
}

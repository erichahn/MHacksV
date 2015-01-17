

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dynamixel.h"

int main(int argc, char**argv)
{
    int sockfd,n;
    struct sockaddr_in servaddr, cliaddr;
    char sendline[1000];
    struct Leap_Messages recvLeap;

    if (argc != 2)
    {
        printf("usage: %s <IP dest address>\n", argv[0]);
        exit(1);
    }

    if( (sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("socket");
        exit(1);
    };

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(argv[1]);
    servaddr.sin_port=htons(32000);

    while (1)
    {
        // block
        n=recvfrom(sockfd,&recvLeap,sizeof(struct Leap_Messages),0,NULL,NULL);
        printf(
            "x_pos %f\n"
            "y_pos %f\n"
            "x_vel %f\n"
            "y_vel %f\n",
            recvLeap.x_pos, recvLeap.y_pos,
            recvLeap.x_vel, recvLeap.y_vel
            );
        printf("\n");
        //usleep();
    }
}





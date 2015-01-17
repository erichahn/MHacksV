

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dynamixel.h"
#include "common.h"

void movePlayer(Dynamixel& dynx, Dynamixel& dyny, int sockfd)
{

        struct Leap_Messages recvLeap;
        printf("reading..\n");
        int n=recvfrom(sockfd,&recvLeap,sizeof(struct Leap_Messages),0,NULL,NULL);
        if (n <= 0)
        {
            perror("recvfrom");
        }
        printf(
            "x_pos %f\n"
            "y_pos %f\n"
            "x_vel %f\n"
            "y_vel %f\n",
            recvLeap.x_pos, recvLeap.y_pos,
            recvLeap.x_vel, recvLeap.y_vel
            );
        printf("\n");
        
        dynx.set_position(recvLeap.x_pos/max_x_pos);
        dyny.set_position(recvLeap.y_pos/max_y_pos);
    
}

int main(int argc, char**argv)
{
    int  player1,player2,n;
    struct sockaddr_in servaddr, cliaddr;
    char sendline[1000];
    struct Leap_Messages recvLeap;
/*
    if (argc != 2)
    {
        printf("usage: %s <IP dest address>\n", argv[0]);
        exit(1);
    }
*/
    if( (player1 = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("socket");
        exit(1);
    };
    if( (player2 = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("socket");
        exit(1);
    };


    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY; // bind to all
    servaddr.sin_port = htons(PORT);

	if (bind(player1, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) 
    {
        perror("bind"); 
        exit(1);
    }
    // player2 plays on next port
    servaddr.sin_port = htons(PORT+1);

    if (bind(player2, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) 
    {
        perror("bind"); 
        exit(1);
    }
 
    Dynamixel x1(1), y1(2);
    Dynamixel x2(3), y2(4);

    fd_set fdset;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 1000;

    FD_ZERO(&fdset);
    FD_SET(player1, &fdset);
    FD_SET(player2, &fdset);

    // run dat game
    while (1)
    {
        select(player1 > player2 ? player1+1 : player2 +1, &fdset, NULL, NULL, NULL);
        
        if (FD_ISSET(player1, &fdset)){
            printf("set1\n");
            movePlayer(x1, y1, player1);
        }

        if (FD_ISSET(player2, &fdset)){
            printf("set2\n");
            movePlayer(x2, y2, player2);
        }

    }

    return 0;
}





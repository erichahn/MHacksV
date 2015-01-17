
// #include "dynamixel.h"


/* Sample UDP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char**argv)
{
    int sockfd,n;
    struct sockaddr_in servaddr, cliaddr;
    char sendline[1000];
    char recvline[1000];

    if (argc != 2)
    {
        printf("usage: %s <IP dest address>\n", argv[0]);
        exit(1);
    }

    if( sockfd = socket(AF_INET,SOCK_DGRAM,0) < 0)
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
        n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
        recvline[n]=0;
        fputs(recvline,stdout);
    }
}





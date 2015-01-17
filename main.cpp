#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>

#define PORT 2000

using std::cout;
using std::cerr;
using std::endl;
using std::string;

struct __attribute__((__packed__)) Leap_Messages {
	float x_pos;
	float z_pos;
	float x_vel;
	float z_vel;
};

int main() {
	int sockfd, newsockfd, maxfd;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	fd_set read_fds, temp_fds;
	struct timeval tv;
	
	FD_ZERO(&read_fds);
	FD_ZERO(&temp_fds);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		cout << "Can't open socket" << endl;
		exit 1;
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		cout << "Can't bind socket" << endl;
		exit 1;
	}

	FD_SET(socketfd, &read_fds);
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	maxfd = sockfd;
	listen(sockfd, 5);

	while (true) {
		temp_fds = read_fds;
		
		if (select(maxfd + 1, &temp_fds, NULL, NULL, &tv) < 0)
		
		if ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &sizeof(cli_addr))) < 0) {
			cout << "Error on accept" << endl;
		}
	
		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);
		
		if (n < 0) {
			error("ERROR reading from socket");
		}
	
		printf("Here is the message: %s",buffer);
	
		n = write(newsockfd, "I got your message", 18);
		
		if (n < 0) {
			error("ERROR writing to socket");
		}
	}

	return 0;
}
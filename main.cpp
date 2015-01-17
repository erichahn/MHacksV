#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <iostream>
#include <string>

#define PORT      2000
#define IP        "192.168.1.3"
#define LOOPDELAY 10000

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
	int sockfd;
	struct sockaddr_in serv_addr, cli_addr;
	struct hostent *hp;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		cout << "Can't open socket" << endl;
		exit(1);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		cout << "Can't bind socket" << endl;
		exit(1);
	}

	string ip = IP;
	memset((char *)&cli_addr, 0, sizeof(cli_addr));
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_port = htons(PORT);
	hp = gethostbyname(ip.c_str());
	memcpy((void *)&cli_addr.sin_addr, hp->h_addr_list[0], hp->h_length);
	float count = 0;

	while (true) {
		struct Leap_Messages mess;
		mess.x_pos = count++;
		mess.z_pos = count++;
		mess.x_vel = count++;
		mess.z_vel = count++;
		int code = sendto(sockfd, (char *)&mess, 16, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
		string error = strerror(errno);
		cout << error << " " << code << endl;
		usleep(10000);
	}

	return 0;
}
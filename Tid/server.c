#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#define BUF_SIZE 32/8
#define THE_70_YEAR_OFFSET 2208988800L

int requestCount = 0;

void signalHandler(int signal) {
	printf("Shutting down server, handled a total of %d request%s.\n", requestCount, requestCount == 1 ? "" : "s");
	exit(0);
}

int main(int argc, char **argv) {
	signal(SIGINT, signalHandler);
	if (argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(0);
	}

	int port = atoi(argv[1]);
	int sockfd;
	struct sockaddr_in si_me, si_other;
	unsigned char buffer[BUF_SIZE];

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&si_me, '\0', sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(port);
	si_me.sin_addr.s_addr = INADDR_ANY;

	bind(sockfd, (struct sockaddr*) &si_me, sizeof(si_me));
	printf("Server started.\n");
	socklen_t addr_size = sizeof(si_other);
	while (1) {
		recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr*) &si_other, &addr_size);

		time_t curtime;
		time(&curtime);
		time_t time = htonl(curtime + THE_70_YEAR_OFFSET);
		sendto(sockfd, &time, BUF_SIZE, 0, (struct sockaddr*) &si_other, addr_size);
		printf("Connection from (%s:%d): %s\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), ctime(&curtime));
		requestCount++;
	}

	return 0;
}

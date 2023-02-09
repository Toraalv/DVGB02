#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define BUF_SIZE 512

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(0);
	}

	int port = atoi(argv[1]);
	int sockfd;
	struct sockaddr_in si_me, si_other;
	char buffer[BUF_SIZE];
	socklen_t addr_size;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&si_me, '\0', sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(port);
	si_me.sin_addr.s_addr = INADDR_ANY;

	bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));
	printf("[+]Socket bound to server address\n");
	addr_size = sizeof(si_other);
	while (1) {
		recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr*)&si_other, &addr_size);

        time_t curtime;
        time(&curtime);
        char* nuvarande_tid = ctime(&curtime);

        sendto(sockfd, nuvarande_tid, BUF_SIZE, 0, (struct sockaddr*)&si_other, addr_size);
		printf("[+]Data send: %s\n", nuvarande_tid);
		sleep(1);
	}

	return 0;
}
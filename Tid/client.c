#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define BYTE_SIZE 8
#define BUF_SIZE 32/BYTE_SIZE
#define THE_70_YEAR_OFFSET 2208988800L

time_t timeDecoder();

int main(int argc, char **argv) {
	// argument management
	if (argc != 2) {
		printf("Incorrect number of arguments supplied. Usage: `%s <port>`\n", argv[0]);
		return 1;
	}

	int port = atoi(argv[1]);

	time_t localTime;
	time(&localTime);
	printf("Local information:\n\tLocal time: %s\n", ctime(&localTime));

	int socket_fd;
	struct sockaddr_in address;
	char received_time[BUF_SIZE];

	socket_fd = socket(PF_INET, SOCK_DGRAM, 0);
	
	memset(&address, '\0', sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

	printf("Sending UDP packet:\n\tIP address: %s\n\tPort: %d\n\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
	sendto(socket_fd, NULL, 0, 0, (struct sockaddr*) &address, sizeof(address));	

	printf("Getting reply:\n\tWaiting for reply: ");
	socklen_t bsAddrVar = sizeof(address);
	int packet_size = recvfrom(socket_fd, received_time, BUF_SIZE, 0, (struct sockaddr*) &address, &bsAddrVar);
	printf("Received\n");
	printf("\tPacket size: %d-bit (%s)\n\n", packet_size * BYTE_SIZE, packet_size * BYTE_SIZE == 32 ? "correct" : "incorrect");

	time_t magicTimeData = timeDecoder(received_time);

	printf("Time format:\n\tValid date: %s\n\tEndian: %s\n\tDate: %s\n",
			magicTimeData == -1 ? "No" : "Yes",
			*(char *)&received_time == 1 ? "Little Endian" : "Big Endian",
			//1 ? "1900 (correct)" : "1970 (incorrect)",
			ctime(&magicTimeData)
	);

	if (magicTimeData == localTime) {
		printf("\nTime appears to match.\n");
	}
	return 0;
}

time_t timeDecoder(char* rec_time) {
	time_t localTime = strtol(rec_time, NULL, 2) - THE_70_YEAR_OFFSET;
	return strtol(rec_time, NULL, 2) - THE_70_YEAR_OFFSET;//time(&localTime);
}

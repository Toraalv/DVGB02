#include "checksum.h"

int make_checksum(struct pkt packet) {
	int cumSum = 0;
	for (int i = 0; packet.payload[i] != '\0'; i++)
		cumSum += packet.payload[i];
	cumSum += packet.acknum;
	cumSum += packet.seqnum;
	return cumSum;
}

bool verify_checksum(struct pkt packet) {
	return make_checksum(packet) == packet.checksum;
}
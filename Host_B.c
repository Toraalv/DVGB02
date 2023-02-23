#include "Sim_Engine.h"
#include "Host_B.h"

/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
	/* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {
	/* TODO */
	printf("b input:\tseqnum: %d\n\t\tacknum: %d\n\t\tchecksum: %d\n\t\tpayload: %s\n", packet.seqnum, packet.acknum, packet.checksum, packet.payload);
	// todo: checksum validation
	packet.acknum = 0; // is this prep needed?
	if(verify_checksum(packet, packet.checksum) == false) { // not OK
		packet.acknum = 1; // shit went down man
	} else { // OK
		tolayer5(B, packet.payload);
	}
	tolayer3(B, packet); // send ACK back
}

/* Called when B's timer goes off */
void B_timerinterrupt() {
	/* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() {
	/* TODO */
}

bool verify_checksum(struct pkt packet, int checksum) {
	int cumSum = 0;
	for (int i = 0; packet.payload[i] != '\0'; i++) {
		cumSum += packet.payload[i];
	}
	cumSum = cumSum + packet.acknum;
	cumSum = cumSum - packet.seqnum;
	printf("cummerSummer: %d, %d\n", cumSum, checksum);
	
	return cumSum == checksum;
}
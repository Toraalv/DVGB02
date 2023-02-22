#include "Sim_Engine.h"


/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
	/* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {
	/* TODO */
	printf("yoyo bitches, jag vet inte om det var korrupt, men jag fick paket som fan\n");
	printf("b input:\tseqnum: %d\n\t\tacknum: %d\n\t\tchecksum: %d\n\t\tpayload: %s\n", packet.seqnum, packet.acknum, packet.checksum, packet.payload);
	// todo: checksum validation
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

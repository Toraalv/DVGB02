#include "Sim_Engine.h"
#include "Host_A.h"
#include <string.h>

/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {
	printf("data: %s\n", message.data);
	/* TODO */
	// skicka detta till andra sidan
	int seqnum = 0;
	struct pkt sending_packet;
	sending_packet.seqnum = seqnum;
	sending_packet.acknum = 0;
	strcpy(sending_packet.payload, message.data);
	//B_input(sending_packet);
	tolayer3(B, sending_packet); // send the packet to B
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
	printf("layer 3:\tseqnum: %d\n\t\tacknum: %d\n\t\tchecksum: %d\n\t\tpayload: %s\n", packet.seqnum, packet.acknum, packet.checksum, packet.payload);
	/* TODO */
	// tydligen kommmer detta från B
}

/* Called when A's timer goes off */
void A_timerinterrupt() {
	printf("en sån jävljarns timer\n");
	/* TODO */
	// "This routine will be called when A's timer expires (thus generating a timer interrupt). You'll probably want to use this routine to control the retransmission of packets. See starttimer() and stoptimer() below for how the timer is started and stopped."
}  

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() {
	printf("init som fan\n");
	/* TODO */
}

#include "Sim_Engine.h"
#include "Host_B.h"
#include "checksum.h"

static bool nextExpected = 1;

/* Called from layer 5, passed the data to be sent to other side */
void B_output( struct msg message) {
	/* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {
	if(!verify_checksum(packet)) { // inte OK
		packet.seqnum = nextExpected;
		packet.acknum = !nextExpected; // nu blev det lite SUS #amongus
		packet.checksum = make_checksum(packet);
		tolayer3(B, packet); // skicka ACK tillbaka
		return;
	} else if (nextExpected == packet.seqnum) { // OK
		tolayer5(B, packet.payload);
		nextExpected = !nextExpected;
	}
	tolayer3(B, packet); // skicka ACK tillbaka (annars blev det lite roligt att A skickade samma paket on repeat som lunch och B bara satt och gick "okej, en duplicate" men inte svarade "ja jag fick ditt skitpaket men gjorde inget med det")
}

/* Called when B's timer goes off */
void B_timerinterrupt() {
	/* TODO */
}  

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() {
	/* TODO */ // Nej.
}

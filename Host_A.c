#include "Sim_Engine.h"
#include "Host_A.h"
#include "checksum.h"

#define timeoutTime 1000

bool isTimer = false;

struct pkt *pktQueue;
int pktQueueLen = 0;
bool seqNum = 0, ackNum = 0; // då kan vi bara flippa dem

/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {
	ackNum = !ackNum; // flippa dem
	seqNum = !seqNum;
	struct pkt sending_packet;
	sending_packet.seqnum = seqNum;
	sending_packet.acknum = ackNum;
	strcpy(sending_packet.payload, message.data);
	sending_packet.checksum = make_checksum(sending_packet);
	enqueue(sending_packet);
	if (!isTimer)
		send_packet(sending_packet);
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
	stoptimer(A);
	isTimer = false;
	if (packet.acknum != packet.seqnum || !verify_checksum(packet)) {
		send_packet(pktQueue[0]);
	} else {
		dequeue();
		// fortsätt skicka tills kön är tom
		if (pktQueueLen != 0) // skicka nästa paket i listan till B
			send_packet(pktQueue[0]);
	}
}

void send_packet(struct pkt puck) {
	isTimer = true;
	tolayer3(A, puck); // send the packet to B
	starttimer(A, timeoutTime);
}

/* Called when A's timer goes off */
void A_timerinterrupt() {
	send_packet(pktQueue[0]); // timade ut, skicka om
}

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() {
	/* TODO */ // nej
}

void enqueue(struct pkt item) {
	struct pkt *newQueue = (struct pkt *)malloc((pktQueueLen + 1) * sizeof(struct pkt)); // allokera en till
	for (int i = 0; i < pktQueueLen; i++)
		newQueue[i] = pktQueue[i];
	newQueue[pktQueueLen] = item;
	free(pktQueue); // :-)
	pktQueue = newQueue;
	pktQueueLen++;
}

void dequeue() { // remove the first item from the array
	for (int i = 0; i < pktQueueLen - 1; i++)
		pktQueue[i] = pktQueue[i + 1]; // copium, tänkte jag, men det fungerar asballt asså // martin
	pktQueueLen--;
}

void print_queue() {
	for (int i = 0; i < pktQueueLen; i++)
		printf("Queue %d: %s\n", i, pktQueue[i].payload);
}

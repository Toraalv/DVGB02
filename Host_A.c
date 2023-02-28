#include "Sim_Engine.h"
#include "Host_A.h"
#include <string.h>

#define timeoutTime 1000

bool isTimer = false;

struct pkt *pktQueue;
int pktQueueLen = 0;
bool seqNum = 0, ackNum = 0; // då kan vi bara flippa dem

/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {
	printf("data: %s\n", message.data);
	/* TODO */
	// skicka detta till andra sidan
	struct pkt sending_packet;
	sending_packet.seqnum = seqNum;
	sending_packet.acknum = ackNum;
	strcpy(sending_packet.payload, message.data);
	sending_packet.checksum = make_checksum(sending_packet);
	enqueue(sending_packet);
	if (!isTimer) {
		send_packet(sending_packet);
	}
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
	stoptimer(A);
	isTimer = false;
	if (packet.acknum == packet.seqnum) {
		ackNum = !ackNum; // flippa dem
		seqNum = !seqNum;
		// printf("layer 3:\tseqnum: %d\n\t\tacknum: %d\n\t\tchecksum: %d\n\t\tpayload: %s\n", packet.seqnum, packet.acknum, packet.checksum, packet.payload);
		dequeue();
	} else {
		send_packet(packet);
		return; // vi vill absolut inte fortsätta med nästa paket om det är så att vi just nu kör om detta istället, vet du
	}

	// keep sending if not empty
	if (pktQueueLen > 0) { // send the next packet to B
		send_packet(pktQueue[0]);
	}
}

void send_packet(struct pkt puck) {
	tolayer3(A, puck); // send the packet to B
	starttimer(A, timeoutTime);
	isTimer = true;
}

/* Called when A's timer goes off */
void A_timerinterrupt() {
	tolayer3(A, pktQueue[0]);
	starttimer(A, timeoutTime);
	/* TODO */
	// "This routine will be called when A's timer expires (thus generating a timer interrupt). You'll probably want to use this routine to control the retransmission of packets. See starttimer() and stoptimer() below for how the timer is started and stopped."
}  

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() {
	printf("init som fan\n");
	/* TODO */
}

int make_checksum(struct pkt packet) { // todo: på structen, inte bara payload/meddelandet
	int cumSum = 0;
	for (int i = 0; packet.payload[i] != '\0'; i++) {
		cumSum += packet.payload[i];
	}
	cumSum = cumSum + packet.acknum;
	cumSum = cumSum + packet.seqnum;
	return cumSum;
}

void enqueue(struct pkt item) {
	struct pkt *newQueue = (struct pkt *)malloc((pktQueueLen + 1) * sizeof(struct pkt)); // alloc one more
	for (int i = 0; i < pktQueueLen; i++) {
		newQueue[i].acknum = pktQueue[i].acknum;
		newQueue[i].seqnum = pktQueue[i].seqnum;
		strcpy(newQueue[i].payload, pktQueue[i].payload);
		newQueue[i].checksum = pktQueue[i].checksum;
	}
	newQueue[pktQueueLen] = item;
	pktQueue = newQueue; // Minneslucka, men kbry
	pktQueueLen++;
}

void dequeue() { // remove the first item from the array
	for (int i = 0; i < pktQueueLen - 1; i++) {
		pktQueue[i] = pktQueue[i + 1]; // kopium
	}
	pktQueueLen--;
}

void print_queue() {
	for (int i = 0; i < pktQueueLen; i++)
		printf("Queue %d: %s\n", i, pktQueue[i].payload);
}

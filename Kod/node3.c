#include "node.h"

struct distance_table dt3;
static void printdt3(struct distance_table *dtptr);

/* Students to write the following two routines, and maybe some others */

void rtinit3() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			dt3.costs[i][j] = 999;
	}

	dt3.costs[3][3] = 0;
	dt3.costs[0][3] = 7;
	dt3.costs[2][3] = 2;

	struct rtpkt initial_broadcast = { .destid = INT_MAX, .sourceid = 3 };
	// tack för att ni gör goda lösningar som leder till att vi inte bara kan dra en memcpy(initial_broadcast.mincost, dt0.costs[0], sizeof(dt0.costs[0]));
	for (int i = 0; i < TABLE_LEN; i++) {
		initial_broadcast.mincost[i] = dt3.costs[i][3]; // 何で
	}

	distribute_packet(initial_broadcast);
}

void rtupdate3(struct rtpkt *rcvdpkt) {
	bool changed = false;
	if (rcvdpkt->destid == 3) { // paketet är vårt
		// todo: kolla om dett finns bättre rutter nu än vad vi har, och uppdatera
		for (int i = 0; i < sizeof(rcvdpkt->mincost) / sizeof(rcvdpkt->mincost[3]); i++) {
			if (rcvdpkt->sourceid == i) continue;
			printf("from %d, %d: rcvdpkt mincost: %d, dt3.costs: %d\n", rcvdpkt->sourceid, i, rcvdpkt->mincost[i], dt3.costs[i][3]);
			if (rcvdpkt->mincost[i] < dt3.costs[i][3]) {
				dt3.costs[i][3] = rcvdpkt->mincost[i];
				changed = true;
			}
		}
	} else { // endast forwarda paketet
		distribute_packet(*rcvdpkt);
		printf("forwarding magi!");
	}

	if (changed) { // om det var vårt paket ska vi broadcasta att vi har förändrats
		struct rtpkt new_broadcast = { .destid = INT_MAX, .sourceid = 3 };
		for (int i = 0; i < TABLE_LEN; i++) {
			new_broadcast.mincost[i] = dt3.costs[i][3]; // 何で mink-ost
		}

		distribute_packet(new_broadcast);
		printdt3(&dt3);
	}
}

void printdt3(struct distance_table *dtptr) {
	printf("             via     \n");
	printf("   D3 |    0     2 \n");
	printf("  ----|-----------\n");
	printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
	printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
	printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
}

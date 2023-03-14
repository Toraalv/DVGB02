#include "node.h"

struct distance_table dt2;
static void printdt2(struct distance_table *dtptr);

/* Students to write the following two routines, and maybe some others */

void rtinit2() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			dt2.costs[i][j] = 999;
	}

	dt2.costs[2][2] = 0;
	dt2.costs[0][2] = 3;
	dt2.costs[1][2] = 1;
	dt2.costs[3][2] = 2;

	struct rtpkt initial_broadcast = { .destid = INT_MAX, .sourceid = 2 };
	// tack för att ni gör goda lösningar som leder till att vi inte bara kan dra en memcpy(initial_broadcast.mincost, dt0.costs[0], sizeof(dt0.costs[0]));
	for (int i = 0; i < TABLE_LEN; i++) {
		initial_broadcast.mincost[i] = dt2.costs[i][2]; // 何で
	}

	distribute_packet(initial_broadcast);
}

void rtupdate2(struct rtpkt *rcvdpkt) {
	bool changed = false;
	if (rcvdpkt->destid == 2) { // paketet är vårt
		// todo: kolla om dett finns bättre rutter nu än vad vi har, och uppdatera
		for (int i = 0; i < sizeof(rcvdpkt->mincost) / sizeof(rcvdpkt->mincost[2]); i++) {
			if (rcvdpkt->sourceid == i) continue;
			printf("from %d, %d: rcvdpkt mincost: %d, dt2.costs: %d\n", rcvdpkt->sourceid, i, rcvdpkt->mincost[i], dt2.costs[i][2]);
			if (rcvdpkt->mincost[i] < dt2.costs[i][2]) {
				dt2.costs[i][2] = rcvdpkt->mincost[i];
				changed = true;
			}
		}
	} else { // endast forwarda paketet
		distribute_packet(*rcvdpkt);
		printf("forwarding magi!");
	}

	if (changed) { // om det var vårt paket ska vi broadcasta att vi har förändrats
		struct rtpkt new_broadcast = { .destid = INT_MAX, .sourceid = 2 };
		for (int i = 0; i < TABLE_LEN; i++) {
			new_broadcast.mincost[i] = dt2.costs[i][2]; // 何で mink-ost
		}

		distribute_packet(new_broadcast);
		printdt2(&dt2);
	}
}

void printdt2(struct distance_table *dtptr) {
	printf("                via     \n");
	printf("   D2 |    0     1    3 \n");
	printf("  ----|-----------------\n");
	printf("     0|  %3d   %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][1],dtptr->costs[0][3]);
	printf("dest 1|  %3d   %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][1],dtptr->costs[1][3]);
	printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][1],dtptr->costs[3][3]);
}

#include "node.h"

struct distance_table dt1;

/* Students to write the following two routines, and maybe some others */

void rtinit1() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			dt1.costs[i][j] = 999;
	}

	dt1.costs[1][1] = 0;
	dt1.costs[0][1] = 1;
	dt1.costs[2][1] = 1;

	struct rtpkt initial_broadcast = { .destid = INT_MAX, .sourceid = 1 };
	// tack för att ni gör goda lösningar som leder till att vi inte bara kan dra en memcpy(initial_broadcast.mincost, dt0.costs[0], sizeof(dt0.costs[0]));
	for (int i = 0; i < TABLE_LEN; i++) {
		initial_broadcast.mincost[i] = dt1.costs[i][1]; // 何で
	}

	distribute_packet(initial_broadcast);
}

void rtupdate1(struct rtpkt *rcvdpkt) {
	/* TODO */
}

void printdt1(struct distance_table *dtptr) {
	printf("             via   \n");
	printf("   D1 |    0     2 \n");
	printf("  ----|-----------\n");
	printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
	printf("dest 2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
	printf("     3|  %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][2]);
}

void linkhandler1(int linkid, int newcost) {
	/* DON'T CHANGE */
}

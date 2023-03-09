#include "node.h"

struct distance_table dt3;

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
	/* TODO */
}

void printdt3(struct distance_table *dtptr) {
	printf("             via     \n");
	printf("   D3 |    0     2 \n");
	printf("  ----|-----------\n");
	printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
	printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
	printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
}

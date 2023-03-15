#include "node.h"

#define NODE_ID 2

static struct distance_table dt;
static void printdt2(struct distance_table *dtptr);

/* Students to write the following two routines, and maybe some others */

void rtinit2() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			dt.costs[i][j] = 999;
	}

	dt.costs[NODE_ID][NODE_ID] = 0;
	dt.costs[0][NODE_ID] = 3;
	dt.costs[1][NODE_ID] = 1;
	dt.costs[3][NODE_ID] = 2;

	struct rtpkt initial_broadcast = { .destid = INT_MAX, .sourceid = NODE_ID };
	for (int i = 0; i < TABLE_LEN; i++) {
		initial_broadcast.mincost[i] = dt.costs[i][NODE_ID];
	}

	distribute_packet(initial_broadcast);
}

void rtupdate2(struct rtpkt *rcvdpkt) {
	rtupdate(rcvdpkt, &dt);
	if (TRACE >= 3) {
		printf("\033[0;31m");
		printdt2(&dt);
		printf("\033[0m\n");
	}
}

void printdt2(struct distance_table *dtptr) {
	printf("   D2 |    0     1    3 \n");
	printf("  ----|-----------------\n");
	printf("     0|  %3d   %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][1],dtptr->costs[0][3]);
	printf("dest 1|  %3d   %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][1],dtptr->costs[1][3]);
	printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][1],dtptr->costs[3][3]);
}

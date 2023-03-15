#include "node.h"

#define NODE_ID 3

static struct distance_table dt;
static void printdt3(struct distance_table *dtptr);

/* Students to write the following two routines, and maybe some others */

void rtinit3() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			dt.costs[i][j] = 999;
	}

	dt.costs[NODE_ID][NODE_ID] = 0;
	dt.costs[0][NODE_ID] = 7;
	dt.costs[2][NODE_ID] = 2;

	struct rtpkt initial_broadcast = { .destid = INT_MAX, .sourceid = NODE_ID };
	for (int i = 0; i < TABLE_LEN; i++) {
		initial_broadcast.mincost[i] = dt.costs[i][NODE_ID];
	}

	distribute_packet(initial_broadcast);
}

void rtupdate3(struct rtpkt *rcvdpkt) {
	rtupdate(rcvdpkt, &dt);
	if (TRACE >= 3) {
		printf("\033[0;33m");
		printdt3(&dt);
		printf("\033[0m\n");
	}
}

void printdt3(struct distance_table *dtptr) {
	printf("   D3 |    0     2 \n");
	printf("  ----|-----------\n");
	printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]); // 0 2
	printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]); // 1 1
	printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]); // 2 0
}

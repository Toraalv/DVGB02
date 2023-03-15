#include "node.h"

#define NODE_ID 0

static struct distance_table dt;
static void printdt0(struct distance_table *dtptr);

/* Students to write the following two routines, and maybe some others */

void rtinit0() { // "Bulding dispaly start" -MARS
	for (int i = 0; i < TABLE_LEN; i++) {
		for (int j = 0; j < TABLE_LEN; j++)
			dt.costs[i][j] = 999;
	}

	dt.costs[NODE_ID][NODE_ID] = 0;
	dt.costs[1][NODE_ID] = 1;
	dt.costs[2][NODE_ID] = 3;
	dt.costs[3][NODE_ID] = 7;

	struct rtpkt initial_broadcast = { .destid = INT_MAX, .sourceid = NODE_ID };
	// tack för att ni gör goda lösningar som leder till att vi inte bara kan dra en memcpy(initial_broadcast.mincost, dt.costs[0], sizeof(dt.costs[0]));
	for (int i = 0; i < TABLE_LEN; i++) {
		initial_broadcast.mincost[i] = dt.costs[i][NODE_ID]; // 何で mink-ost
	}

	distribute_packet(initial_broadcast);
}

void rtupdate0(struct rtpkt *rcvdpkt) {
	rtupdate(rcvdpkt, &dt);
	if (TRACE >= 3) {
		printf("\033[0;32m");
		printdt0(&dt);
		printf("\033[0m\n");
	}
}

void printdt0(struct distance_table *dtptr) {
	printf("   D0 |    1     2    3 \n");
	printf("  ----|-----------------\n");
	printf("     1|  %3d   %3d   %3d\n", dtptr->costs[1][1], dtptr->costs[1][2],dtptr->costs[1][3]);
	printf("dest 2|  %3d   %3d   %3d\n", dtptr->costs[2][1], dtptr->costs[2][2],dtptr->costs[2][3]);
	printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][1], dtptr->costs[3][2],dtptr->costs[3][3]);
}

void linkhandler0(int linkid, int newcost) {
	/* DON'T CHANGE */
	// ok
}

#include "node.h"

struct distance_table dt0;

//static void printdt0(struct distance_table *dtptr);

/* Students to write the following two routines, and maybe some others */

void rtinit0() {
	for (int i = 0; i < TABLE_LEN; i++) {
		for (int j = 0; j < TABLE_LEN; j++)
			dt0.costs[i][j] = 999;
	}

	dt0.costs[0][0] = 0;
	dt0.costs[1][0] = 1;
	dt0.costs[2][0] = 3;
	dt0.costs[3][0] = 7;

	struct rtpkt initial_broadcast = { .destid = INT_MAX, .sourceid = 0 };
	// tack för att ni gör goda lösningar som leder till att vi inte bara kan dra en memcpy(initial_broadcast.mincost, dt0.costs[0], sizeof(dt0.costs[0]));
	for (int i = 0; i < TABLE_LEN; i++) {
		initial_broadcast.mincost[i] = dt0.costs[i][0]; // 何で
	}

	distribute_packet(initial_broadcast);

	printbettertable(&dt0);
}

void rtupdate0(struct rtpkt *rcvdpkt) {
	printf("din mor\n");
	// todo: kolla om dett finns bättre rutter nu än vad vi har, och uppdatera
}

void printdt0(struct distance_table *dtptr) {
	printf("                via     \n");
	printf("   D0 |    1     2    3 \n");
	printf("  ----|-----------------\n");
	printf("     1|  %3d   %3d   %3d\n", dtptr->costs[1][1], dtptr->costs[1][2],dtptr->costs[1][3]);
	printf("dest 2|  %3d   %3d   %3d\n", dtptr->costs[2][1], dtptr->costs[2][2],dtptr->costs[2][3]);
	printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][1], dtptr->costs[3][2],dtptr->costs[3][3]);
}

void linkhandler0(int linkid, int newcost) {
	/* DON'T CHANGE */
}

#include "node.h"

void printbettertable(struct distance_table *dtptr) {
	printf("      |    0     1     2    3 \n");
	printf("  ----|-----------------------\n");
	printf("     0|  %3d   %3d   %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][1], dtptr->costs[0][2], dtptr->costs[0][3]);
	printf("     1|  %3d   %3d   %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][1], dtptr->costs[1][2], dtptr->costs[1][3]);
	printf("     2|  %3d   %3d   %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][1], dtptr->costs[2][2], dtptr->costs[2][3]);
	printf("     3|  %3d   %3d   %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][1], dtptr->costs[3][2], dtptr->costs[3][3]);
}

void distribute_packet(struct rtpkt pkt) {
	// skicka packetet till alla アホ noder
	for (int i = 0; i < TABLE_LEN; i++) {
		if (i == pkt.sourceid) continue;
        if ((pkt.sourceid % 2 == 1) && (i == 3 || i == 1)) continue;
		pkt.destid = i;
		tolayer2(pkt);
	}
}
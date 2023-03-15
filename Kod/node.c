#include "node.h"

void distribute_packet(struct rtpkt pkt) { // ブロードキャストタイム！！！
	// skicka packetet till alla アホ noder
	for (int i = 0; i < TABLE_LEN; i++) {
		if (i == pkt.sourceid) continue;
        if ((pkt.sourceid % 2 == 1) && (i % 2 == 1)) continue; // finns ingen koppling mellan 1 och 3. :-)
		pkt.destid = i;
		tolayer2(pkt);
	}
}

// vi tycker att det är trevligare att inte kopiera kod i varje nodfil :-)
void rtupdate(struct rtpkt *rcvdpkt, struct distance_table *dt) {
	bool changed = false;
	int node_id = rcvdpkt->destid; // vi

	// går igenom alla värden i paketets (mink)ost
	for (int i = 0; i < sizeof(rcvdpkt->mincost) / sizeof(rcvdpkt->mincost[0]); i++) {
		// kollar ifall den nya vägen mellan källnoden och destinationsnoden är mindre än den redan sparade vägen mellan källnoden och i
		if ((rcvdpkt->mincost[i] + dt->costs[rcvdpkt->sourceid][node_id]) < dt->costs[i][rcvdpkt->sourceid]) {
			dt->costs[i][rcvdpkt->sourceid] = rcvdpkt->mincost[i] + dt->costs[rcvdpkt->sourceid][node_id]; // ändra vikten till den nya och bättre vägen
			changed = true;
		}
	}

	if (changed) {
		struct rtpkt upt_table = { .destid = INT_MAX, .sourceid = node_id };
		for (int i = 0; i < TABLE_LEN; i++) { // hämtar bästa rutt smidigt som fan
			int best_route = dt->costs[i][node_id];
			for (int j = 0; j < TABLE_LEN; j++) {
				if (dt->costs[i][j] < best_route)
					best_route = dt->costs[i][j];
			}
			upt_table.mincost[i] = best_route; // spara vår bästa rutt
		}
		distribute_packet(upt_table); // levererar puck :-)
	}
}

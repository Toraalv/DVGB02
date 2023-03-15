#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h> // INT_MAX ベービ！
#include "sim_engine.h"

#define TABLE_LEN 4

extern int TRACE;
// extern int YES, NO; // budget booleans, vi importerar

struct distance_table {
	int costs[4][4];
};

extern void distribute_packet(struct rtpkt);
extern void rtupdate(struct rtpkt *rcvdpkt, struct distance_table *dt);

#endif
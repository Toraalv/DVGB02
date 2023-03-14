#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "sim_engine.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table {
	int costs[4][4];
};

extern void printbettertable(struct distance_table *dtptr);
extern void distribute_packet(struct rtpkt);

#define TABLE_LEN 4

#endif
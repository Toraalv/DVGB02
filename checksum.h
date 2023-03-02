#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdbool.h>
#include "Sim_Engine.h"

int make_checksum(struct pkt payload);
bool verify_checksum(struct pkt packet);

#endif
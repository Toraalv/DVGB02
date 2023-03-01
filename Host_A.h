#ifndef HOST_A_H
#define HOST_A_H

#include <stdbool.h>
#include <string.h>

void A_output(struct msg message);
void A_input(struct pkt packet);
void send_packet(struct pkt puck);
void A_timerinterrupt();
void A_init();
void enqueue(struct pkt item);
void dequeue();
void print_queue();

#define A 0
#define B 1

#endif

#ifndef HOST_B_H
#define HOST_B_H

void B_output(struct msg message);
void B_input(struct pkt packet);
void B_timerinterrupt();
void B_init();

#endif

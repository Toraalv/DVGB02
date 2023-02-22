#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H


#include <stdio.h>
#include <stdlib.h>

/* DON'T CHANGE */
#define BIDIRECTIONAL 0

/* You can check the simulated time using the time variable */
extern float time;

/* A "msg" is the data unit passed from layer 5 (implemented in simulator) to layer  */
/* 4 (students' code).  It contains the data (characters) to be delivered            */
/* to layer 5 via the students transport level protocol entities.                    */
struct msg {
  char data[20];
};

/* A packet is the data unit passed from layer 4 (students code) to layer */
/* 3 (teachers code).  Note the pre-defined packet structure, which all   */
/* students must follow. */
struct pkt {
   int seqnum;
   int acknum;
   int checksum;
   char payload[20];
};

/* A or B is trying to stop timer */
void stoptimer(int AorB);  

/* A or B is trying to start timer */
void starttimer(int AorB, float increment);  

/* Invoked by A or B to deliver packet to layer 3 */
void tolayer3(int AorB, struct pkt packet);  

/* Invoked by A or B to deliver paqcket to layer 5 (application layer) */
void tolayer5(int AorB,char datasent[20]);
  

#endif

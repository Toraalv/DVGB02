#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

/* a rtpkt is the packet sent from one routing update process to
   another via the call tolayer3() */
struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

void rtinit0(void);
void rtinit1(void);
void rtinit2(void);
void rtinit3(void);

void rtupdate0(struct rtpkt *rcvdpkt);
void rtupdate1(struct rtpkt *rcvdpkt);
void rtupdate2(struct rtpkt *rcvdpkt);
void rtupdate3(struct rtpkt *rcvdpkt);

void linkhandler0(int linkid, int newcost);
void linkhandler1(int linkid, int newcost);
void linkhandler2(int linkid, int newcost);
void linkhandler3(int linkid, int newcost);

void tolayer2(struct rtpkt packet);

#endif

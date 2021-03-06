#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include "ipvs.h"

#define NUM_SCHEDULERS  30

void add_services();
void add_schedulers();
void add_dest(int scheds, int addr, int port, int weight);
void update_dest(int scheds, int addr ,int port, int nw);
void delete_dest(int scheds, int pn,  int addr, int port);
void add_service(int pnId);
void add_dests(int sid, int addr, int port, int weight);
struct ip_vs_dest* load();
void view_dests(int scheds);

#endif

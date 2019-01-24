#ifndef IPVS_SCHED_H
#define IPVS_SCHED_H

#include "ipvs.h"

void ipvs_init_scheduler(struct ip_vs_scheduler **scheduler,
        struct ip_vs_scheduler *sch_user);

void ipvs_add_dest(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler, struct ip_vs_dest *dest);
void ipvs_update_dest(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler, struct ip_vs_dest *dest);
void ipvs_delete_dest(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler, struct ip_vs_dest *dest);
void ipvs_add_service(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler);
void ipvs_remove_service(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler);
struct ip_vs_dest* ipvs_scheduler(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler);

#endif

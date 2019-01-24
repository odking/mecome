#include "list.h"
#include "ipvs.h"
#include <assert.h>

void ipvs_init_scheduler(struct ip_vs_scheduler **scheduler,
        struct ip_vs_scheduler *sch_user)
{
    assert(scheduler != NULL);
    *scheduler = sch_user;
}

void ipvs_add_dest(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler, struct ip_vs_dest *dest)
{

    list_add(&dest->n_list, &svc->destinations);
    svc->num_dests++;
    scheduler->add_dest(svc, dest);

}

void ipvs_update_dest(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler, struct ip_vs_dest *dest)
{
    DBG_FUN;

    scheduler->upd_dest(svc, dest);

    DBG_FUN_DONE;
}

void ipvs_delete_dest(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler, struct ip_vs_dest *dest)
{
    DBG_FUN;
    list_del(&dest->n_list);
    svc->num_dests--;
    scheduler->del_dest(svc, dest);
    DBG_FUN_DONE;
}

void ipvs_add_service(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler)
{
    assert(svc != NULL);
    assert(scheduler != NULL);
    scheduler->init_service(svc);
}

void ipvs_remove_service(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler)
{
    DBG_FUN;
    scheduler->done_service(svc);
    DBG_FUN_DONE;
}

struct ip_vs_dest* ipvs_scheduler(struct ip_vs_service *svc, struct ip_vs_scheduler* scheduler)
{
    scheduler->schedule(svc);
}


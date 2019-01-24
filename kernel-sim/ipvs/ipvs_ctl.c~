#include "ipvs.h"
#include "list.h"
#include "ipvs_sched.h"
#include "ipvs_ctl.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


static LIST_HEAD(ip_vs_schedulers);

struct ip_vs_scheduler* schedulers[30] = {NULL};
struct ip_vs_service  service[30] = {0};

void add_services(int svcs)
{
    for (int i = 0; i < svcs; i++)
    {
        service[i].fwmark = 0x8888;
        INIT_LIST_HEAD(&service[i].destinations);
        ipvs_add_service(&service[i], schedulers[i]);
    }
}

void add_schedulers(int scheds)
{
    for (int i = 0; i < scheds; i++)
        ipvs_init_scheduler(&schedulers[i], register_wrr_scheduler());
}

static struct ip_vs_dest *
lookup_dest(struct ip_vs_service *svc, int addr, int port)
{
    struct ip_vs_dest *dest;

    list_for_each_entry(dest, &svc->destinations, n_list) {
        if ((dest->addr == addr) &&
                (dest->port == port)) {
            return dest;
        }
    }

    return NULL;
}


void add_dest(int scheds, int addr, int port, int weight)
{
    for (int i = 0; i < scheds; i++)
    {
        if (NULL == lookup_dest(&service[i], addr, port))
        {
            struct ip_vs_dest* dest = (struct ip_vs_dest*)malloc(sizeof(struct ip_vs_dest));
            memset((void*)dest, 0, sizeof(struct ip_vs_dest));
            dest->flags  = IP_VS_DEST_F_AVAILABLE;
            dest->svc = &service[i];
            dest->vfwmark = service[i].fwmark;
            dest->addr = addr;
            dest->port = port;
            dest->weight = weight;
            /*  INIT_HLIST_NODE(&dest->d_list);*/

            ipvs_add_dest(&service[i], schedulers[i], dest);
        }
    }
}

void update_dest(int scheds, int addr ,int port, int nw)
{
    for (int i = 0; i < scheds; i++)
    {
        if (service[i].fwmark == 0x8888)
        {
            struct ip_vs_dest *dest = lookup_dest(&service[i], addr, port);
            assert(dest != NULL);
            dest->weight = nw;

            ipvs_update_dest(&service[i], schedulers[i], dest); 
        }
    }
}

void delete_dest(int scheds, int pn, int addr, int port)
{
    struct ip_vs_dest *dest2, *nxt;
    for (int i = 0; i < scheds; i++)
    {
        struct ip_vs_dest* dest = lookup_dest(&service[i], addr, port);
        assert(dest != NULL);
        ipvs_delete_dest(&service[i], schedulers[i], dest);
        free(dest);
    }

    list_for_each_entry_safe(dest2, nxt, &service[pn].destinations, n_list) {
        ipvs_delete_dest(&service[pn], schedulers[pn], dest2);
        free(dest2);
    }
    ipvs_remove_service(&service[pn], schedulers[pn]);
    memset((void*)&service[pn], 1, sizeof(struct ip_vs_service));
    service[pn].fwmark = 0;

    list_for_each_entry_safe(dest2, nxt, &service[pn+1].destinations, n_list) {
        ipvs_delete_dest(&service[pn+1], schedulers[pn+1], dest2);
        free(dest2);
    }
    ipvs_remove_service(&service[pn+1], schedulers[pn+1]);
    service[pn+1].fwmark = 0;
    memset((void*)&service[pn+1], 0, sizeof(struct ip_vs_service));

    schedulers[pn] = NULL;
    schedulers[pn+1] = NULL;
}

void add_service(int pn)
{
    ipvs_init_scheduler(&schedulers[pn], register_wrr_scheduler());
    ipvs_init_scheduler(&schedulers[pn+1], register_wrr_scheduler());

    service[pn].fwmark = 0x8888;
    INIT_LIST_HEAD(&service[pn].destinations);
    ipvs_add_service(&service[pn], schedulers[pn]);
    service[pn+1].fwmark = 0x8888;
    INIT_LIST_HEAD(&service[pn+1].destinations);
    ipvs_add_service(&service[pn+1], schedulers[pn+1]);

}

void add_dests(int sid, int addr, int port, int weight)
{
    if (NULL == lookup_dest(&service[sid], addr, port))
    {
        struct ip_vs_dest* dest = (struct ip_vs_dest*)malloc(sizeof(struct ip_vs_dest));
        memset((void*)dest, 0, sizeof(struct ip_vs_dest));
        dest->flags  = IP_VS_DEST_F_AVAILABLE;
        dest->svc = &service[sid];
        dest->vfwmark = service[sid].fwmark;
        dest->addr = addr;
        dest->port = port;
        dest->weight = weight;
        /*  INIT_HLIST_NODE(&dest->d_list);*/

        ipvs_add_dest(&service[sid], schedulers[sid], dest);
    }
}

struct ip_vs_dest* load(int scheds)
{
    static int i = 0;
    struct ip_vs_dest *dest;

    while (service[i].fwmark != 0x8888)
    {
        i = (i + 1) % NUM_SCHEDULERS;
    }
    dest = ipvs_scheduler(&service[i], schedulers[i]);
    i = (i + 1) % NUM_SCHEDULERS;
    return dest;
}

void view_dests(int scheds)
{
    struct ip_vs_dest *dest;
    for (int i = 0; i < scheds; i++)
    {
        if (service[i].fwmark == 0x8888)
        {
            list_for_each_entry(dest, &service[i].destinations, n_list) {
                printf("scheduler[%d], addr %d port %d weight %d svc %d\n",
                        i, dest->addr, dest->port, dest->weight, dest->svc);
            }
        }
    }
}







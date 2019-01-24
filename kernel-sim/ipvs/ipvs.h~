#ifndef IPVS_H
#define IPVS_H

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define IP_VS_DEST_F_AVAILABLE  0x0001      /* server is available */
#define IP_VS_DEST_F_OVERLOAD   0x0002      /* server is overloaded */

#define __fun__ __FUNCTION__
#define DBG_FUN  /* printf("%s\n", __fun__)*/
#define DBG_FUN_DONE  /*printf("%s done!\n", __fun__)*/

#define ip_vs_scheduler_err printf
#define IP_VS_DBG_BUF /*printf*/



struct ip_vs_dest {
    struct list_head    n_list;   /* for the dests in the service */
    struct hlist_node   d_list;   /* for table with all the dests */

    int          port;       /* port number of the server */
    int  addr;       /* IP address of the server */
    volatile unsigned int   flags;      /* dest status flags */
    int        weight;     /* server weight */

    /* connection counters and thresholds */
    int        activeconns;    /* active connections */
    int        persistconns;   /* persistent connections */
    int           u_threshold;    /* upper threshold */
    int           l_threshold;    /* lower threshold */

    /* for destination cache */

    /* for virtual service */
    struct ip_vs_service  *svc;    /* service it belongs to */
     int           vfwmark;    /* firewall mark of service */

};

/*
 *  * The information about the virtual service offered to the net and the
 *   * forwarding entries.
 *    */
struct ip_vs_service {
    struct hlist_node   s_list;   /* for normal service table */
    struct hlist_node   f_list;   /* for fwmark-based service table */

    int                   fwmark;   /* firewall mark of the service */
    unsigned int        timeout;  /* persistent timeout in ticks */
    int          netmask;  /* grouping granularity, mask/plen */

    struct list_head    destinations;  /* real server d-linked list */
    int           num_dests;     /* number of servers */

    /* for scheduling */
    struct ip_vs_scheduler  *scheduler; /* bound scheduler object */
    void            *sched_data;   /* scheduler application data */

};

/* The scheduler object */
struct ip_vs_scheduler {
    struct list_head    n_list;     /* d-linked list head */
    char            *name;      /* scheduler name */

    /* scheduler initializing service */
    int (*init_service)(struct ip_vs_service *svc);
    /* scheduling service finish */
    void (*done_service)(struct ip_vs_service *svc);
    /* dest is linked */
    int (*add_dest)(struct ip_vs_service *svc, struct ip_vs_dest *dest);
    /* dest is unlinked */
    int (*del_dest)(struct ip_vs_service *svc, struct ip_vs_dest *dest);
    /* dest is updated */
    int (*upd_dest)(struct ip_vs_service *svc, struct ip_vs_dest *dest);

    /* selecting a server from the given service */
    struct ip_vs_dest* (*schedule)(struct ip_vs_service *svc);
};

struct ip_vs_scheduler* register_wrr_scheduler();
#endif

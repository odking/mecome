#include "list.h"
#include "ipvs.h"
#include "ipvs_ctl.h"

#include <stdlib.h>
#include <stdio.h>


#define swap(a, b) \
        do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)

/* The WRR algorithm depends on some caclulations:
 ** current destination pointer for weighted round-robin scheduling
 **/
struct ip_vs_wrr_mark {
    struct ip_vs_dest *cl;  /* current dest or head */
    int cw;         /* current weight */
    int mw;         /* maximum weight */
    int di;         /* decreasing interval */
};

unsigned long gcd(unsigned long a, unsigned long b)
{
    unsigned long r;

    if (a < b)
        swap(a, b);

    if (!b)
        return a;
    while ((r = a % b) != 0) {
        a = b;
        b = r;
    }
    return b;
}

static int ip_vs_wrr_gcd_weight(struct ip_vs_service *svc)
{
    struct ip_vs_dest *dest;
    int weight;
    int g = 0;

    list_for_each_entry(dest, &svc->destinations, n_list) {
        weight = dest->weight;
        if (weight > 0) {
            if (g > 0)
                g = gcd(weight, g);
            else
                g = weight;
        }
    }
    return g ? g : 1;
}

/*
 *  *    Get the maximum weight of the service destinations.
 *   */
static int ip_vs_wrr_max_weight(struct ip_vs_service *svc)
{
    struct ip_vs_dest *dest;
    int new_weight, weight = 0;

    list_for_each_entry(dest, &svc->destinations, n_list) {
        new_weight = dest->weight;
        if (new_weight > weight)
            weight = new_weight;
    }

    return weight;
}


static int ip_vs_wrr_init_svc(struct ip_vs_service *svc)
{
    struct ip_vs_wrr_mark *mark;

    /*
     *   *    Allocate the mark variable for WRR scheduling
     *       */
    mark = malloc(sizeof(struct ip_vs_wrr_mark));
    if (mark == NULL)
        return -100;

    mark->cl = list_entry(&svc->destinations, struct ip_vs_dest, n_list);
    mark->di = ip_vs_wrr_gcd_weight(svc);
    mark->mw = ip_vs_wrr_max_weight(svc) - (mark->di - 1);
    mark->cw = mark->mw;
    svc->sched_data = mark;

    return 0;
}


static void ip_vs_wrr_done_svc(struct ip_vs_service *svc)
{
    
    free(svc->sched_data);
    svc->sched_data = NULL;
}


static int ip_vs_wrr_dest_changed(struct ip_vs_service *svc,
        struct ip_vs_dest *dest)
{
    struct ip_vs_wrr_mark *mark = svc->sched_data;

    mark->cl = list_entry(&svc->destinations, struct ip_vs_dest, n_list);
    mark->di = ip_vs_wrr_gcd_weight(svc);
    mark->mw = ip_vs_wrr_max_weight(svc) - (mark->di - 1);
    if (mark->cw > mark->mw || !mark->cw)
        mark->cw = mark->mw;
    else if (mark->di > 1)
        mark->cw = (mark->cw / mark->di) * mark->di + 1;
    return 0;
}


/*
 *  *    Weighted Round-Robin Scheduling
 *   */
    static struct ip_vs_dest *
ip_vs_wrr_schedule(struct ip_vs_service *svc)
{
    struct ip_vs_dest *dest, *last, *stop = NULL;
    struct ip_vs_wrr_mark *mark = svc->sched_data;
    int last_pass = 0, restarted = 0;

    dest = mark->cl;
    /* No available dests? */
    if (mark->mw == 0)
        goto err_noavail;
    last = dest;
    /* Stop only after all dests were checked for weight >= 1 (last pass) */
    while (1) {
        list_for_each_entry_continue(dest, &svc->destinations, n_list) {
            if (!(dest->flags & IP_VS_DEST_F_OVERLOAD) &&
                    dest->weight >= mark->cw)
                goto found;
            if (dest == stop)
                goto err_over;
        }
        mark->cw -= mark->di;
        if (mark->cw <= 0) {
            mark->cw = mark->mw;
            /* Stop if we tried last pass from first dest:
             ** 1. last_pass: we started checks when cw > di but
             **  then all dests were checked for w >= 1
             ** 2. last was head: the first and only traversal
             **  was for weight >= 1, for all dests.
             *            */
            if (last_pass ||
                    &last->n_list == &svc->destinations)
                goto err_over;
            restarted = 1;
        }
        last_pass = mark->cw <= mark->di;
        if (last_pass && restarted &&
                &last->n_list != &svc->destinations) {
            /* First traversal was for w >= 1 but only
             *           * for dests after 'last', now do the same
             *                       * for all dests up to 'last'.
             *                                   */
            stop = last;
        }
    }

found:
    IP_VS_DBG_BUF("WRR: server %d:%d "
            "activeconns %d  weight %d\n",
            dest->addr, dest->port,
            dest->activeconns,
            dest->weight);
    mark->cl = dest;

out:
    return dest;

err_noavail:
    mark->cl = dest;
    dest = NULL;
    ip_vs_scheduler_err("no destination available");
    goto out;

err_over:
    mark->cl = dest;
    dest = NULL;
    ip_vs_scheduler_err("no destination available: "
            "all destinations are overloaded");
    goto out;
}

static struct ip_vs_scheduler ip_vs_wrr_scheduler = {
    .name =         "wrr",
    .n_list =       LIST_HEAD_INIT(ip_vs_wrr_scheduler.n_list),
    .init_service =     ip_vs_wrr_init_svc,
    .done_service =     ip_vs_wrr_done_svc,
    .add_dest =     ip_vs_wrr_dest_changed,
    .del_dest =     ip_vs_wrr_dest_changed,
    .upd_dest =     ip_vs_wrr_dest_changed,
    .schedule =     ip_vs_wrr_schedule,
};

struct ip_vs_scheduler* register_wrr_scheduler()
{
    return &ip_vs_wrr_scheduler;
}



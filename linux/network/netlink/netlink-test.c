/*
 * =====================================================================================
 *
 *       Filename:  netlink-mod.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/16/2020 02:05:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jinqing Yan (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/netlink.h>
#include <net/netlink.h>
#include <net/net_namespace.h>
#define NETLINK_TEST 31

#define NLMSG_PONG 0x11
#define NLMSG_PING 0x12
static struct sock *sk;
static void nltest_rcv(struct sk_buff *skb);

int __init nltest_net_init(void)
{
    struct netlink_kernel_cfg cfg = {
        .input = nltest_rcv,
    };
    sk = netlink_kernel_create(&init_net, NETLINK_TEST, &cfg);
    if (!sk) {
        printk(KERN_INFO "netlink create error!\n");
        return -ENOMEM;
    }
    printk(KERN_INFO "nltest initialed successfully!\n");
    return 0;
}

void __exit nltest_net_exit(void)
{
    netlink_kernel_release(sk);
    printk(KERN_INFO "nltest exit...\n");
}

static int nltest_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
    void *payload;
    struct sk_buff *out_skb;
    void *out_payload;
    struct nlmsghdr *out_nlh;
    int payload_len; // with padding, but ok for echo
    switch(nlh->nlmsg_type)
    {
        case NLMSG_PONG:
            break;
        case NLMSG_PING:
            payload = nlmsg_data(nlh);
            payload_len = nlmsg_len(nlh);
            printk(KERN_INFO "Recievid: %s, From: %d\n", (char *)payload, nlh->nlmsg_pid);

            out_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
            out_nlh = nlmsg_put(out_skb, 0, 0, NLMSG_PONG, payload_len, 0);
            out_payload = nlmsg_data(out_nlh);
            strcpy(out_payload, "[from kernel]:");
            strcat(out_payload, "pong");
            nlmsg_unicast(sk, out_skb, nlh->nlmsg_pid);
            break;
        default:
            printk(KERN_INFO "Unknow msgtype recieved!\n");
    }
    return 0;
failure:
    printk(KERN_INFO " failed in fun dataready!\n");
    return 0;
}

static void nltest_rcv(struct sk_buff *skb)
{
    netlink_rcv_skb(skb, &nltest_rcv_msg);
}

module_init(nltest_net_init);
module_exit(nltest_net_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("a simple example");
MODULE_AUTHOR("hello world");

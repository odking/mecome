#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/netlink.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#define NETLINK_TEST 31
#define NLMSG_PONG 0x11
#define NLMSG_PING 0x12
#define MAX_PAYLOAD 101

struct sockaddr_nl src_addr, dst_addr;
struct iovec iov;
int sockfd;
struct nlmsghdr *nlh = NULL;
struct msghdr msg;

int main( int argc, char **argv)
{
    sockfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_TEST);
    bzero(&src_addr, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();
    src_addr.nl_groups = 0;
    bind(sockfd, (struct sockaddr*)&src_addr, sizeof(src_addr));

    bzero(&dst_addr, sizeof(dst_addr));
    dst_addr.nl_family = AF_NETLINK;
    dst_addr.nl_pid = 0;
    dst_addr.nl_groups = 0;
    nlh = malloc(NLMSG_SPACE(MAX_PAYLOAD));  
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = NLM_F_REQUEST;
    nlh->nlmsg_type = NLMSG_PING;
    strcpy(NLMSG_DATA(nlh), "ping");
    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;

    msg.msg_name = (void *)&dst_addr;
    msg.msg_namelen = sizeof(dst_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    printf("ping kernel ing...\n");
    sendmsg(sockfd, &msg, 0);
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));

    recvmsg(sockfd, &msg, 0);
    printf(" Received message payload: %s\n", NLMSG_DATA(nlh));
    return 0;
}

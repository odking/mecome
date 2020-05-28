
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdarg.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netpacket/packet.h>

#include <linux/if_ether.h>
#include <netinet/ether.h>


#define DEFAULT_INTERFACE "eth0"
struct  dest_t {
	/* link layer (standard - not vlan) */
	unsigned char dstmac[6];
	unsigned char srcmac[6];
        /* unsigned short vlantype;
	unsigned short vtag; */
	unsigned short ethertype;
	/* ipv6 header */
	__u32 vcf;   /*concat of version, class, and flow */
	__u16 length;
	__u8 nextheader;
	__u8 hoplimit;
	__u8 srcadd[16];
	__u8 dstadd[16];
	/* following is the icmpv6 stuff */
	__u8 type;
	__u8 code;
	__u16 cksum;
	__u32 unused;
	__u8 old_packet[24];
} __attribute__((packed));

int debug = 0;
int times = 1;
int wait = 1000;
unsigned char mymac[ETHER_ADDR_LEN];
char interface[64];
struct in6_addr src_addr;
struct in6_addr dst_addr;
unsigned char dst_mac[6];


void dbgfun(char *format, ...)
{
     if (! debug) return;
     va_list list; 
     va_start(list, format);
          fprintf(stderr, "dbg: ");
          vfprintf(stderr, format, list);
          fprintf(stderr, "\n");
          fflush(stderr);
     va_end(list);
     return;
}

void usage(char *prog)
{
	printf("%s -s <src_addr> -d <dst_addr> -D <dst_mac> "
               "\n"
               "Optional arguments:\n"
               "-v - activate debug printing\n"
               "-t <address> target address in ipv6 notation\n"
               "-i <interface> the interface to send on, defaults to eth0\n"
               "-n <times> - the number of packets to send, default 1\n"
               "-w <msecs> - number of msecs between sent packets, default 1000\n",
               prog);
}

int
parse_opts(int argc, char **argv)
{
	int c, rc;
	int res = 0;
	while ((c = getopt(argc, argv, "hvd:s:D:i:n:w:")) != EOF) {
		switch (c) {
                        case 'h':
                        case '?':
                                usage(argv[0]);
                                return -1;
                        case 'v':
                                debug = 1;
                                dbgfun("Activated debug printing on stderr");
                                break;
                        case 'w':
                                wait = atoi(optarg);
                                break;
                        case 'n':
                                times = atoi(optarg);
                                break;
                        case 's':  /* ipv6 source address */
                                res = inet_pton(AF_INET6, optarg, &src_addr);
                                if(res < 0){
                                        perror("inet_pton");
                                        return -1;
                                }
                                if(res == 0){
                                        fprintf(stderr, "Illegal IPv6 address\n");
                                        return -1;
                                }
                                break;
                        case 'd':  /* ipv6 destination address */
                                res = inet_pton(AF_INET6, optarg, &dst_addr);
                                if(res < 0){
                                        perror("inet_pton");
                                        return -1;
                                }
                                if(res == 0){
                                        fprintf(stderr, "Illegal IPv6 address\n");
                                        return -1;
                                }
                                break;
                        case 'i':  /* interface to send out on */
                                strcpy(interface, optarg);
                                break;
                        case 'D':
                                rc = sscanf(optarg, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                                            &dst_mac[0],
                                            &dst_mac[1],
                                            &dst_mac[2],
                                            &dst_mac[3],
                                            &dst_mac[4],
                                            &dst_mac[5]);
                                if (rc != 6)
                                        perror("failed to parse mac addr\n");
                                break;
		}
        }
        if(!res) return -1; /* -t option is required */
        return 1;
}


int get_mac(int fd, char *dev)
{
     struct ifreq info;
     memset(&info, 0, sizeof info);
     memcpy(&info.ifr_name, dev, strlen(dev));
     /* read resulting mac into info.ifr_hwaddr
      * it comes back in host order already
      */
     if (ioctl(fd, SIOCGIFHWADDR, &info) == -1){
          perror("error ioctl reading mac ");
          return -1;
     }
     memcpy(mymac, &info.ifr_hwaddr.sa_data, ETHER_ADDR_LEN);
     dbgfun("mac address for: %s is: %s", dev, ether_ntoa((struct ether_addr*)&mymac));
     return 1;
}


int new_raw_socket(char *ethernetdevice, unsigned short protocol)
{
     int rawsock;
     struct ifreq interfaceinfo;
     struct sockaddr_ll bindaddr;
     dbgfun("new_raw_socket: interface: %s protocol: %hu",
	    ethernetdevice, protocol);
     memset(&bindaddr, 0, sizeof bindaddr);
     memset(&interfaceinfo, 0, sizeof interfaceinfo);
     memcpy(&interfaceinfo.ifr_name, ethernetdevice, strlen(ethernetdevice));
     
     if ((rawsock = socket(PF_PACKET, SOCK_RAW, htons(protocol))) == -1){
	  perror("Failed opening raw socket");
	  return -1;
     }

     /* map interface name to index */
     if (ioctl(rawsock, SIOCGIFINDEX, &interfaceinfo) == -1){
	  perror("ioctl SIOCGIFINDEX");
	  return -1;
     }
     
     bindaddr.sll_family = AF_PACKET;
     bindaddr.sll_protocol = htons(protocol);
     bindaddr.sll_ifindex = interfaceinfo.ifr_ifindex;
     
     if (bind(rawsock, (struct sockaddr *)&bindaddr, sizeof(struct sockaddr_ll)) == -1){
	  perror("Failed binding raw socket");
	  return -1;
     }
     dbgfun("Opened/bound raw socket interface index %u for %s, protocol %hu",
	    interfaceinfo.ifr_ifindex, interfaceinfo.ifr_name, protocol);
     return rawsock;
}

__u16
icmp_checksum(struct dest_t *dest){
/* 16 bit ones complement over ipv6 pseudo header and the
 * icmpv6 payload (checksumfield set to 0).
 * pseudo header is 16byte src, 16byte dest, 4byte upperlayer length,
 * 3byte set to zero , and 1byte nextheader
 *
 * NOTE!
 * this little gem works only if there is an even number of octets
 * in the part being checksummed.
 */
	int loop;
	__u32 checksum = 0;
	__u16 *cksp;

	cksp = (__u16*) &(dest->srcadd);
	for (loop=0;loop<16;loop+=2) checksum += *(cksp++);

	cksp = (__u16*) &(dest->dstadd);
	for (loop=0;loop<16;loop+=2) checksum += *(cksp++);

	checksum += dest->length; /* the extra two bytes are zero */
	checksum += dest->nextheader<<8; /* the extra three bytes are zero */


	cksp = (__u16*)&(dest->type);
	for (loop=0;loop<ntohs(dest->length);loop+=2) checksum += *(cksp++);

	checksum = (checksum>>16) + (checksum & 0xffff); /* add the carry */
	checksum += (checksum>>16); /* and any carry from the above */
				/* should there be carry from the carry, we give up */

	/* return 0x57a7; */
	return ~checksum & 0xffff;
}



/* main Main MAIN */
int
main(int argc, char **argv)
{
        int rawsock;
        unsigned short protocol;

        struct dest_t dest;

        int sloop;
        int res;
        int i;
        /* all nodes multicast FF02:0:0:0:0:0:0:1 */
        // unsigned char allnodesmulti[] = { 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
        /* multicast mac for above (hex) 33:33:00:00:00:01 */
        // unsigned char multimac[] = { 0x33, 0x33, 0x00, 0x00, 0x00, 0x01 };
        /*
         * not used target address in icmpv6 message is used as srcaddress in the ipv6 packet
         unsigned char localipv6add[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        */

        strcpy(interface, DEFAULT_INTERFACE);
        if(parse_opts(argc, argv) <0){
                fprintf(stderr, "Bad options\n");
                exit(1);
        }


        protocol = 58; /* ipv6-icmp from /etc/protocols */
        protocol = ETH_P_IPV6; /* from if_ether.h */

        dbgfun("Params Interface: %s Protocol: %u\n"
               "Times to send: %u, Interval: %u\n", interface, protocol, times, wait);
        memset(&dest, 0, sizeof dest);

        rawsock = new_raw_socket(interface, protocol);

        if(get_mac(rawsock, interface) < 0){
                perror("get_mac");
                exit(1);
        }
        memcpy(dest.dstmac, dst_mac, ETHER_ADDR_LEN);
        memcpy(dest.srcmac, mymac, ETHER_ADDR_LEN);
        dest.ethertype = htons(ETH_P_IPV6);
        dest.vcf = htonl(6<<28); /* ip version 6 */
        dest.length = htons(32); /* length of the icmpv6 data */
        dest.nextheader = 58 /* icmpv6 */;
        dest.hoplimit = 255;
        memcpy(dest.srcadd, src_addr.s6_addr, sizeof src_addr.s6_addr);
        memcpy(dest.dstadd, dst_addr.s6_addr, sizeof dst_addr.s6_addr);
        dest.type = 1; /* destination unreachable */
        dest.code = 4; /* port unreachable */
        dest.cksum = 0;
        dest.unused = 0;
        for ( i = 0; i < sizeof(dest.old_packet); i++ )
                dest.old_packet[i] = i;

        dest.cksum = icmp_checksum(&dest); 

        for(sloop=0; sloop<times; sloop++){
                if(sloop) usleep(wait * 1000);
                res = write(rawsock, &dest, sizeof dest);
                dbgfun("Write returned: %u\n", res);
                if(res == -1){
                        perror("write to socket failed");
                        return 1;
                }
        }
        return 0;
} /* end of main */

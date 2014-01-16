/* af-packet-dump */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "hexdump.h"

#define BZ 16384
#define PROTOCOL 0x88cc

int
main(int argc, char *argv[])
{
	int fd;
	unsigned char buf[BZ];
	ssize_t len;

	fd = socket(AF_PACKET, SOCK_RAW, htons(PROTOCOL));
	if(fd < 0) {
		perror("opening socket");
		exit(1);
	}

	len = 1;
	while (len > 0) {
		struct sockaddr_ll sll;
		socklen_t slen = sizeof(sll);
		struct ifreq ifr;

		len = recvfrom(fd, buf, BZ, 0, (struct sockaddr *)&sll, &slen);
		if (len <= 0) continue;

		memset(&ifr, 0x0, sizeof(ifr));
		ifr.ifr_ifindex = sll.sll_ifindex;
		ioctl(fd, SIOCGIFNAME, &ifr);
		fprintf(stderr, "%ld bytes received interface:%d(%s) type:%d\n", len, sll.sll_ifindex, ifr.ifr_name, sll.sll_pkttype);
		hexdump(stderr, buf, len);
	}

	return 0;
}


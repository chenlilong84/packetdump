/* af-packet-dump */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <net/if.h>

#include "hexdump.h"

#define BZ 16384
#define PROTOCOL 89

int
main(int argc, char *argv[])
{
	int fd;
	unsigned char buf[BZ];
	ssize_t len;

	fd = socket(AF_INET, SOCK_RAW, PROTOCOL);
	if(fd < 0) {
		perror("opening socket");
		exit(1);
	}

	len = 1;
	while (len > 0) {
		struct sockaddr_in sin;
		socklen_t slen = sizeof(sin);

		len = recvfrom(fd, buf, BZ, 0, (struct sockaddr *)&sin, &slen);
		if (len <= 0) continue;

		fprintf(stderr, "%ld bytes received from %s protocol %u\n", len,
			inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
		hexdump(stderr, buf, len);
	}

	return 0;
}


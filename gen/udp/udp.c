#include "udp.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

void fill_in_udp(char *buf, struct s_udphdr *hdr, uint16_t src_port, uint16_t dest_port, uint16_t len, uint8_t checksum_bool)
{
	// no checksum required 
	if(!checksum_bool)
	{
		hdr->sport = htons(src_port);
		hdr->dport = htons(dest_port);
		hdr->len   = htons(len);
		hdr->check = 0;
	
	}
	else
	{
		return; /* checksum for udp is retarded */
	}

	copy_udp_header(buf, hdr);
}


/* pass in buf pointer at the proper offset */
void copy_udp_header(char *buf, struct s_udphdr *hdr)
{
	memcpy(buf, hdr, 8);
}

/* pass in buf pointer at the proper offset */
void degen_udp(char *buf, struct s_udphdr *output)
{
	memcpy(output, buf, 8);
}

void print_udp(struct s_udphdr hdr)
{
	printf("UDP DATA:\n");
	printf("SRC %i\n",ntohs(hdr.sport));
	printf("DST %i\n",ntohs(hdr.dport));
	printf("LEN %i\n",ntohs(hdr.len));
	printf("CHK 0x%x\n",ntohs(hdr.check));
}


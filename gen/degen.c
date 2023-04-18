#include "degen.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

/* DEGEN */
void decompose_hdr_ipv4(char *buf, struct s_iphdr4 *hdr)
{
	uint8_t  *hold_8;
	uint16_t *hold_16;
	uint32_t *hold_32;
	
	hold_8 = (uint8_t *)buf;
	
	hdr->ver_ihl = hold_8[0];
	hdr->dscp_ecn = hold_8[1];

	hdr->ttl = hold_8[8];
	hdr->prot = hold_8[9];
	
	hold_16 = (uint16_t *)buf;

	hdr->len = hold_16[1];
	hdr->ident = hold_16[2];
	hdr->flag_off = hold_16[3];

	hdr->check = hold_16[5];

	hold_32 = (uint32_t *)buf;

	hdr->src = hold_32[3];
	hdr->dest = hold_32[4];
} 

void decompose_hdr_udp(char *buf, struct s_iphdr4 *ihdr, struct s_udphdr *uhdr)
{
	uint8_t size   = ((ihdr->ver_ihl<<4)>>4)*4; 
	
	char *char_hold = (char *)malloc(8);
	memcpy(char_hold,buf+size,8);

	uint16_t *hold = (uint16_t *)char_hold;

	uhdr->sport = hold[0];
	uhdr->dport = hold[1];
	uhdr->len   = hold[2];
	uhdr->check = hold[3];

	free(char_hold);
}

char *decompose_ipv4_ascii(uint32_t addr)
{
	struct in_addr hold;
	hold.s_addr = addr;

	return inet_ntoa(hold);
}

void decompose_bit_ipv4(struct s_iphdr4 *hdr, struct ip_bit_hold *bhold)
{
	bhold->ver = hdr->ver_ihl>>4;
	bhold->ihl = ((hdr->ver_ihl<<4)>>4);

	bhold->dscp = hdr->dscp_ecn>>2;
	bhold->ecn = ((hdr->dscp_ecn<<6)>>6);

	bhold->flag = ntohs(hdr->flag_off)>>10;
	bhold->off = ((ntohs(hdr->flag_off)<<3)>>3);
}

void decompose_udp_print(char *buf)
{
	struct s_iphdr4 hdr;
	decompose_hdr_ipv4(buf,&hdr);
	struct s_udphdr uhdr;
	decompose_hdr_udp(buf,&hdr,&uhdr);

	printf("SRC PORT %i\n",ntohs(uhdr.sport));
	printf("DST PORT %i\n",ntohs(uhdr.dport));
	printf("LEN %i\n",ntohs(uhdr.len));
	printf("CHECK 0x%x\n",uhdr.check);
}

void decompose_ipv4_print(char *buf)
{

	struct s_iphdr4 hdr;
	struct ip_bit_hold bhold;
	
	/* decompose our buf into data */
	decompose_hdr_ipv4(buf,&hdr);
	decompose_bit_ipv4(&hdr,&bhold);

	printf("VERSION %i\n",bhold.ver);
	printf("IHL %i (SIZE %i)\n",bhold.ihl,bhold.ihl*4);
	printf("DSCP %i ECN %i\n",bhold.dscp,bhold.ecn);
	printf("LEN %i\n",ntohs(hdr.len));
	printf("IDENTITY %i\n",ntohs(hdr.ident));
	printf("FLAG %i\n",bhold.flag);
	printf("OFF %i\n",bhold.off);
	printf("TTL %i\n",hdr.ttl);
	printf("PROTOCOL 0x%x\n",hdr.prot);
	printf("CHECKSUM 0x%x\n",hdr.check);
	printf("SRC %s\n",decompose_ipv4_ascii(hdr.src));
	printf("DEST %s\n",decompose_ipv4_ascii(hdr.dest));
}

void decompose_packet_print(char *buf)
{
	struct s_iphdr4 hdr;
	struct ip_bit_hold bhold;
	
	/* decompose our buf into data */
	decompose_hdr_ipv4(buf,&hdr);
	decompose_bit_ipv4(&hdr,&bhold);

	printf("\nVERSION %i\n",bhold.ver);
	printf("IHL %i (SIZE %i)\n",bhold.ihl,bhold.ihl*4);
	printf("DSCP %i ECN %i\n",bhold.dscp,bhold.ecn);
	printf("LEN %i\n",ntohs(hdr.len));
	printf("IDENTITY %i\n",ntohs(hdr.ident));
	printf("FLAG %i\n",bhold.flag);
	printf("OFF %i\n",bhold.off);
	printf("TTL %i\n",hdr.ttl);
	printf("PROTOCOL 0x%x\n",hdr.prot);
	printf("CHECKSUM 0x%x\n",hdr.check);
	printf("SRC %s\n",decompose_ipv4_ascii(hdr.src));
	printf("DEST %s\n",decompose_ipv4_ascii(hdr.dest));

	switch(hdr.prot)
	{
		case P_UDP:
			printf("\nUDP DATA \n");
			decompose_udp_print(buf);	
			break;
		case P_TCP:
			break;
		case P_ICMP:
			break;
	}
}

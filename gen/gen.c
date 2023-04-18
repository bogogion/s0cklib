#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "gen.h"

/* put x + y into a byte */
uint8_t combine_into_byte(uint8_t x, uint8_t y, uint8_t first_shift)
{
	uint8_t temp;
	
	/* Add four bits from x and shift over by first_shift, then do OR on last four bits to put into final bytes */
	temp = (x << first_shift) | y;
	return temp;
}

/* Combines flags and offset */
uint16_t combine_into_flag_off(uint8_t x, uint16_t y)
{
	uint16_t temp;

	temp = (x << 13) | y;
	return temp;
}

/* IPv4 Checksum */
uint16_t calc_csum(uint16_t *ptr,int nbytes) 
{
	uint16_t answer;
	answer = 0;

	while(nbytes)
	{
		answer += *ptr++;
		nbytes--;
	}

	return(~answer);
}

#include <time.h>
#include <stdlib.h>
uint16_t gen_uint16_rand_identity_quick()
{
	srand(time(NULL));
	uint16_t rand_num = rand() % 65535;
	
	while(rand_num == 0)
	{
		rand_num = rand() % 65535;
	}

	return rand_num;
}

uint16_t gen_uint16_rand_identity()
{
	/* read 20 bytes from urandom */
	FILE *fp;
	fp = fopen("/dev/urandom","rb");

	char *buf;
	buf = (char *)malloc(20);
	fgets(buf,20,fp);
	fclose(fp);

	/* sum all the numbers together */
	int seed = 0;
	for(int i = 0; i < 20; i++)
	{ seed += buf[i]; }

	/* seed our random and get our number */
	srand(time(NULL) * seed);
	uint16_t rand_num = rand() % 65535;
	
	while(!rand_num)
	{
		rand_num = rand() % 65535;
	}

	free(buf);

	return rand_num;
}

void create_iphdr_ipv4(struct s_iphdr4 *hdr, struct ip_bit_hold bit_hold, uint16_t length, uint16_t ident, uint8_t ttl, uint8_t proto,
		       uint32_t source, uint32_t dest)
{
	/* Fill in values and properly format combined bytes */
	hdr->ver_ihl = combine_into_byte(bit_hold.ver, bit_hold.ihl, 4);
	hdr->dscp_ecn = combine_into_byte(bit_hold.dscp, bit_hold.ecn, 6);
	hdr->ident = htons(ident);
	hdr->len = htons(length); /* network byte order*/
	hdr->flag_off = htons(combine_into_flag_off(bit_hold.flag,bit_hold.off));
	hdr->ttl = ttl;
	hdr->prot = proto;
	hdr->check = 0;
	hdr->src = source;
	hdr->dest = dest;

	hdr->check = calc_csum((uint16_t *) hdr, (4 * bit_hold.ihl));
}

void create_udp_packet(struct s_udphdr *hdr, struct s_iphdr4 *ihdr, uint16_t sport, uint16_t dport, uint16_t len, int csum_bool)
{
	/* Check if to create checksum*/
	if(!csum_bool)
	{
		hdr->sport  = htons(sport);
		hdr->dport  = htons(dport);
		hdr->len    = htons(len);
		hdr->check  = 0;
	} else
	{
		printf("Checksum currently unavaible, will be needed for IPv6\n");
	}
}

void create_icmp_packet(struct s_icmp *icmp, uint8_t type, uint8_t code, uint32_t data)
{
	icmp->type  = type;
	icmp->code  = code;
	icmp->check = 0;
	icmp->data = data;

	icmp->check = calc_csum((uint16_t *)icmp, 8);
}

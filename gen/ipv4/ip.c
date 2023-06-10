#include "ip.h"
#include "../gen.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

void fill_in_ipv4(char *buf, uint16_t buf_len, struct s_iphdr4 *hdr, struct ip_bit_hold bit_hold, uint16_t length, uint16_t ident, uint8_t ttl,
		  uint8_t proto, uint32_t source, uint32_t dest)
{
	/* Fill in whole header with correct byte order */
	hdr->ver_ihl  = combine_into_byte(bit_hold.ver, bit_hold.ihl, 4);
	hdr->dscp_ecn = combine_into_byte(bit_hold.dscp, bit_hold.ecn, 6);
	hdr->ident    = htons(ident);
	hdr->len      = htons(length);
	hdr->flag_off = htons(combine_into_flag_off(bit_hold.flag, bit_hold.off));
	hdr->ttl      = ttl;
	hdr->prot     = proto;
	hdr->check    = 0;
	hdr->src      = source;
	hdr->dest     = dest;
	hdr->check    = calc_csum((uint16_t *)hdr, (4 * bit_hold.ihl));
	if(buf_len >= (4 * bit_hold.ihl))
	{
		memcpy(buf,hdr,(4 * bit_hold.ihl));
	}
}

uint32_t addr_to_bytes(const char *address)
{
	return(inet_addr(address));
}

void degen_iphdr(char *buf, struct s_iphdr4 *hdr, struct ip_bit_hold bit_hold)
{


}

void print_iphdr(struct s_iphdr4 hdr)
{


}

char *bytes_to_addr(uint32_t address)
{
	struct in_addr *hold;
	hold = (struct in_addr *)malloc(sizeof(struct in_addr));
	
	hold->s_addr = address;
	
	char *chold = inet_ntoa(*hold);
	
	free(hold);

	return chold;
}

#ifndef IPV4
#define IPV4
#include "../packet_def.h"

/* Code for the creation of IPv4 headers, and the degen of them. */

/* Full process into buffer, *hdr must be passed in allocated.
   ALL buffer references assume that pointer is passed in at the CORRECT OFFSET */
void fill_in_ipv4(char *buf, uint16_t buf_len, struct s_iphdr4 *hdr, struct ip_bit_hold bit_hold, uint16_t length, uint16_t ident, uint8_t ttl, 
		  uint8_t proto, uint32_t source, uint32_t dest);
uint32_t addr_to_bytes(const char *address);
void degen_iphdr(char *buf, struct s_iphdr4 *hdr, struct ip_bit_hold bit_hold); 
void print_iphdr(struct s_iphdr4 hdr); 
char *bytes_to_addr(uint32_t address);

#endif

#ifndef IPV4
#define IPV4
#include "../packet_def.h"

/* Code for all current IPV4 functions. Declaration of the IPV4 header structure is defined in packet_def.h and follows
   directly with the proper structure. 

   fill_in_ipv4 puts all the options provided into *buf and into *hdr so that the settings can be reused.

   ALL buffer references assume that the pointer is passed at the correct offset. For all raw sockets that do not need
   the inclusion of an ethernet header, this is generally at offset 0. */

void fill_in_ipv4(char *buf, uint16_t buf_len, struct s_iphdr4 *hdr, struct ip_bit_hold bit_hold, uint16_t length, uint16_t ident, uint8_t ttl, 
		  uint8_t proto, uint32_t source, uint32_t dest);
void copy_ip_header(char *buf, struct s_iphdr4 *hdr); // used internally by fill_in_ipv4
uint32_t addr_to_bytes(const char *address);
void degen_iphdr(char *buf, struct s_iphdr4 *hdr, struct ip_bit_hold *bit_hold); 
void print_iphdr(struct s_iphdr4 hdr, struct ip_bit_hold bit_hold); 
char *bytes_to_addr(uint32_t address);

#endif

/* Include all sub directories */

#include "packet_def.h"
#include "udp/udp.h"
#include "ipv4/ip.h"

#ifndef GEN_H
#define GEN_H

uint8_t  combine_into_byte(uint8_t x, uint8_t y, uint8_t first_shift);
uint16_t combine_into_flag_off(uint8_t x, uint16_t y);
uint16_t calc_csum(uint16_t *ptr, int nbytes);
uint16_t gen_uint16_rand_identity_quick();
uint16_t gen_uint16_rand_identity();

// TODO: move these into respective directories
void create_iphdr_ipv4(struct s_iphdr4 *hdr, struct ip_bit_hold bit_hold, uint16_t length, uint16_t ident, uint8_t ttl, uint8_t proto,
		       uint32_t source, uint32_t dest);
void create_udp_packet(struct s_udphdr *hdr, struct s_iphdr4 *ihdr, uint16_t sport, uint16_t dport, uint16_t len, int csum_bool);
void create_tcp_packet(struct s_tcphdr *output, struct s_tcp pseudo_tcp);
void create_icmp_packet(struct s_icmp *icmp, uint8_t type, uint8_t code, uint32_t data);
#endif

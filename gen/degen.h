#include "packet_def.h"

#ifndef DEGEN_H
#define DEGEN_H
void decompose_hdr_udp(char *buf, struct s_iphdr4 *ihdr, struct s_udphdr *uhdr);
void decompose_hdr_tcp(char *buf); /* TODO: create TCP hdr */
void decompose_hdr_ipv4(char *buf, struct s_iphdr4 *hdr);
void decompose_bit_ipv4(struct s_iphdr4 *hdr, struct ip_bit_hold *bhold);
char *decompose_ipv4_ascii(uint32_t addr);
void decompose_ipv4_print(char *buf);
void decompose_packet_print(char *buf);
void decompose_udp_print(char *buf);
#endif

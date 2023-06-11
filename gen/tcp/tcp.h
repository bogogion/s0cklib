#include "../packet_def.h"

#ifndef TCP_H
#define TCP_H

/* All current TCP functions for basic functionality. This is only for generating TCP packets and NOT for receiving them.

   TCP Checksum is filled with many parts, and for performance it is recommended to reuse pseudo headers, especially in a high
   frequency job, as creating new ones and freeing them creates memory issues and performance drops.

   All buffers provided assume that they are at the correct offset! Also verify that they are of the correct size, as the data is also required
   to peformance TCP functions. */

uint16_t calc_tcp_checksum(struct s_pseudo_ipv4 phdr, struct s_tcphdr thdr, char *data, uint16_t data_size);

void fill_in_tcp(char *buf, struct s_tcp tcp_info, char *data, uint16_t data_size, struct s_pseudo_ipv4 *phdr, struct s_tcphdr *thdr);
void copy_tcp_hdr(char *buf, struct s_tcphdr hdr);
void degen_tcp(char *buf, struct s_tcphdr hdr);
void print_tcp(struct s_tcphdr hdr);

#endif

#ifndef UDP_H
#define UDP_H
#include "../packet_def.h" // UDP structs 

/* Code for all UDP packet generation and processing. 
   For all buffer references the correct offset must be provided. This is traditionally an offset of 20 (assuming a 20 byte ip header)

   Complete declaration of the udp header is in packet_def.h

   Currently UDP checksum is NOT SUPPORTED, and will most likely not be in the future. */

void fill_in_udp(char *buf, struct s_udphdr *hdr, uint16_t src_port, uint16_t dest_port, uint16_t len, uint8_t checksum_bool);
void copy_udp_header(char *buf, struct s_udphdr *hdr); // used internally by fill_in_udp
void degen_udp(char *buf, struct s_udphdr *output);
void print_udp(struct s_udphdr hdr);

#endif

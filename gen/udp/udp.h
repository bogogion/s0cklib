#ifndef UDP_H
#define UDP_H
#include "../packet_def.h" // UDP structs 

/* Code for all UDP packet generation and processing. Includes gen and degen */

void fill_in_udp(char *buf, struct s_udphdr *hdr, uint16_t src_port, uint16_t dest_port, uint16_t len, uint8_t checksum_bool);

/* FOR ALL *buf REFERENCES, MAKE SURE TO PASS THE BUF AT THE CORRECT OFFSET AFTER THE IP HEADER */
void copy_udp_header(char *buf, struct s_udphdr *hdr); 
void degen_udp(char *buf, struct s_udphdr *output);
void print_udp(struct s_udphdr hdr);

#endif

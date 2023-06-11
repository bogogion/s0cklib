#include <stdint.h>

#ifndef PACKET_DEF_H
#define PACKET_DEF_H
/* Protocol types for ipv4 */
#define P_TCP 0x06
#define P_UDP 0x11
#define P_ICMP 0x01

/* Bit hold for ipheader */
struct ip_bit_hold
{
	uint8_t ver : 4;	
	uint8_t ihl : 4;

	uint8_t dscp : 6;
	uint8_t ecn : 2;

	uint8_t flag : 3;
	uint16_t off : 13;
};

/* Complete header */
struct s_iphdr4
{
	uint8_t ver_ihl;
	uint8_t dscp_ecn;

	uint16_t len;
	uint16_t ident;
	uint16_t flag_off;

	uint8_t ttl;
	uint8_t prot;
	
	uint16_t check;

	uint32_t src;
	uint32_t dest;
};

/* UDP */
struct s_udphdr
{
	uint16_t sport;
	uint16_t dport;
	uint16_t len;
	uint16_t check;
};

struct s_pseudo_ipv4
{
	uint32_t src_addr;
	uint32_t dst_addr;

	uint8_t  zero;
	uint8_t  prot;
	uint16_t len;
};

/* TCP */

/* flag codes */
#define T_CWR 1 << 7
#define T_ECE 1 << 6
#define T_URG 1 << 5
#define T_ACK 1 << 4
#define T_PSH 1 << 3
#define T_RST 1 << 2
#define T_SYN 1 << 1
#define T_FIN 1

struct s_tcphdr
{
	uint16_t sport;
	uint16_t dport;
	
	uint32_t seq_num;

	uint32_t ack_num;

	uint8_t  off_res; /* shift off by 4 up to make room for reserved */
	uint8_t  flags;
	uint16_t win_size;
	
	uint16_t check;
	uint16_t urg_p;
};


/* ease of use wrapper for s_tcphdr */
struct s_tcp
{
	uint32_t source_addr, dest_addr;

	uint16_t sport, dport;

	uint32_t seq, ack;

	uint16_t length; /* ipv4 header + tpc header length */

	uint8_t offset : 4;
	uint8_t flag;
	uint16_t win_size, urgency_pointer;
};

/* ICMP */
struct s_icmp
{
	uint8_t  type;
	uint8_t  code;
	uint16_t check;
	
	uint32_t data;
};

#endif

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <stddef.h>
#include "../gen/degen.h"
int create_raw_socket()
{
	return(socket(AF_INET, SOCK_RAW, IPPROTO_RAW));
}

int create_raw_tcp_socket()
{
	return(socket(AF_INET, SOCK_RAW, IPPROTO_TCP));
}

int create_normal_socket(uint8_t tcp_or_udp)
{
	/* 1 for tcp 0 for udp */
	if(tcp_or_udp)
	{
		return(socket(AF_INET, SOCK_STREAM, 0));
	}
	return(socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP));
}

int s_receive(int fd, char *buf, uint32_t buf_len)
{
	/* TODO: potentially setup selecting and polling for the file descriptor */
	return recvfrom(fd, buf, buf_len, 0, NULL, NULL);	
}

int s_receive_specific(int fd, char *buf, uint32_t buf_len, uint32_t source)
{
	/* break down iphdr by shifting up 14 bytes */
	struct s_iphdr4 hdr;
	while(1)
	{
		recvfrom(fd, buf, buf_len, 0, NULL, NULL);
		decompose_hdr_ipv4(buf+14, &hdr);

		if(hdr.src == source)
		{ return 1; } /* success! */
	}
}

int create_rawpacket_receive_socket()
{
	return socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP));
}

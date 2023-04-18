#include <stdint.h>

#ifndef IP4_H
#define IP4_H
int create_raw_socket();
int create_raw_tcp_socket();

/* 1 for TCP 0 for UDP */
int create_normal_socket(uint8_t tcp_or_udp);

void s_sendto();
void s_send();

/* Freezes thread until response received */
int s_receive(int fd, char *buf, uint32_t buf_len);

/* Receives based off source address */
int s_receive_specific(int fd, char *buf, uint32_t buf_len, uint32_t source);

int create_rawpacket_receive_socket();

#endif

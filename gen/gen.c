#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "gen.h"

/* put x + y into a byte */
uint8_t combine_into_byte(uint8_t x, uint8_t y, uint8_t first_shift)
{
	uint8_t temp;
	
	/* Add four bits from x and shift over by first_shift, then do OR on last four bits to put into final bytes */
	temp = (x << first_shift) | y;
	return temp;
}

/* Combines flags and offset */
uint16_t combine_into_flag_off(uint8_t x, uint16_t y)
{
	uint16_t temp;

	temp = (x << 13) | y;
	return temp;
}

/* IPv4 Checksum */
uint16_t calc_csum(uint16_t *ptr,int nbytes) 
{
	uint16_t answer;
	answer = 0;

	while(nbytes)
	{
		answer += *ptr++;
		nbytes--;
	}

	return(~answer);
}

#include <time.h>
#include <stdlib.h>
uint16_t gen_uint16_rand_identity_quick()
{
	srand(time(NULL));
	uint16_t rand_num = rand() % 65535;
	
	while(rand_num == 0)
	{
		rand_num = rand() % 65535;
	}

	return rand_num;
}

/* not as fast but more randomized. use this only for a consistent / repeated connection */

uint16_t gen_uint16_rand_identity()
{
	/* read 20 bytes from urandom */
	FILE *fp;
	fp = fopen("/dev/urandom","rb");

	char *buf;
	buf = (char *)malloc(20);
	fgets(buf,20,fp);
	fclose(fp);

	/* sum all the numbers together */
	int seed = 0;
	for(int i = 0; i < 20; i++)
	{ seed += buf[i]; }

	/* seed our random and get our number */
	srand(time(NULL) * seed);
	uint16_t rand_num = rand() % 65535;
	
	while(!rand_num)
	{
		rand_num = rand() % 65535;
	}

	free(buf);

	return rand_num;
}

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
#endif

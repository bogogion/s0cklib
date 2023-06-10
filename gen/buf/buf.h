#include <stdint.h>
#ifndef BUF_H
#define BUF_H

/* tool for printing stuff */
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

/* buffer tools */
char * create_buf(uint32_t size);
void replace(char *buf, uint32_t size, uint32_t offset, char *replace, uint32_t size_of_replace);
void destroy(char *buf);
char * resize(uint32_t resize, uint32_t previous_size, char *buf);
void clear(char *buf, uint32_t amount_to_clear, uint32_t buf_size, char clear_char);
char * cap_packet(char *buf, uint32_t size); /* add a '\0' to end of packet so it can be printed */

#endif

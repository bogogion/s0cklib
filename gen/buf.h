#include <stdint.h>
#ifndef BUF_H
#define BUF_H

/* buffer tools */
char * create_buf(uint32_t size);
void replace(char *buf, uint32_t size, uint32_t offset, char *replace, uint32_t size_of_replace);
void destroy(char *buf);
char * resize(uint32_t resize, uint32_t previous_size, char *buf);
void clear(char *buf, uint32_t amount_to_clear, uint32_t buf_size, char clear_char);
char * cap_packet(char *buf, uint32_t size); /* add a '\0' to end of packet so it can be printed */

#endif

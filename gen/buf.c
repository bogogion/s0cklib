#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

char * create_buf(uint32_t size)
{
	return (char *)malloc(size);
}

void destroy(char *buf)
{
	free(buf);
}

void clear(char *buf, uint32_t amount_to_clear, uint32_t buf_size, char clear_char)
{
	if(amount_to_clear > buf_size)
	{
		printf("Amount to clear: %i larger than buffer size: %i\n", amount_to_clear, buf_size);
		return;
	}
	
	for(uint32_t i = 0; i < amount_to_clear+1; i++)
	{
		buf[i] = clear_char;
	}
}

char * resize(uint32_t resize, uint32_t previous_size, char *buf)
{
	if(resize == previous_size)
	{
		printf("Resize amount is the same as previous size. Aborting.\n");
		return (char *)-1; // if they fuck up, they fuck up
	}
	
	char *new_buf = create_buf(resize);
	memcpy(new_buf, buf, previous_size);

	destroy(buf);
	return new_buf;
}

void replace(char *buf, uint32_t size, uint32_t offset, char *replace, uint32_t size_of_replace)
{
	/* check if user is replacing something they cant*/
	if((offset) + size_of_replace > size)
	{
		printf("Replace requested is out of bounds of buffer.\n");
		return;
	}

	uint32_t j = 0;
	for(uint32_t i = offset; i < offset+size_of_replace; i++)
	{
		buf[i] = replace[j];
		j++;
	}
}

char * cap_packet(char *buf, uint32_t size)
{
	char *temp = resize(size+1,size,buf);
	
	/* size is og index + 1 anyways */ 
	temp[size] = '\0';
	
	return temp;
}

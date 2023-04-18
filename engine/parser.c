#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void parse_into_tokens(char *buf, int buf_size)
{
	/* loop through buffer and tokenize into out buffer */
	
	int tokens = 100;

	char temp_token[512];
	int j = 0;
	int cur_token = 0;

	char *out_buf[512];

	for(int i = 0; i < buf_size; i++)
	{
		if(buf[i] != ' ' && buf[i] != '\0' )
		{
			temp_token[j] = buf[i];
			j++;
		} else {
			printf("CUR_T %i\n",cur_token);
			out_buf[cur_token] = temp_token;
			printf("BUF %s\n",out_buf[cur_token]);
			cur_token++;

			/* clear us out */
			j = 0;
			memset(&temp_token,0,sizeof(temp_token));
			
			for(int i = 0; i < cur_token; i++)
			{ printf("| %s | %i\n",out_buf[i],i); }

		}
	}

	for(int i = 0; i < cur_token; i++)
	{ printf("| %s | %i\n",out_buf[i],i); }
}

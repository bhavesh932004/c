#include <stdio.h>
#include <stdlib.h>
#include "c_strtok.h"

int main(int argc, char** argv)
{
	if (argc != 4)
		exit(EXIT_FAILURE);

	const char* str = argv[1];
	char* token = NULL;
	while((token = scan_token_alloc_buf(&str, 
					(const char*) argv[2])) != NULL){
		fprintf(stdout, "%s\n", token);
		free(token);
	}
	
	return 0;
}

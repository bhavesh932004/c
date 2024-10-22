#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"

char *read_line(FILE *file_p){
        int buffer_len = 32;
        char *buffer = (char *) malloc(buffer_len * sizeof(char));
        assert_heap_allocation(buffer);
        
        int total_num_read = 0;
        for(;;){
                if(fgets(buffer + total_num_read, buffer_len - total_num_read, file_p) == NULL){
                        free(buffer);
                        return NULL;
                }

                //printf("read : %d %d\n", total_num_read, buffer_len);
                int num_read = strlen(buffer + total_num_read);
                total_num_read += num_read;
                
                //printf("read, total : %d, curr : %d\n", total_num_read, num_read);
                if(buffer[total_num_read - 1] == '\n'){
                        total_num_read--; 
                        break;
                }
                
                if(total_num_read + 1 == buffer_len){
                        buffer_len *= 2;
                        buffer = realloc(buffer, buffer_len);
                        assert_heap_allocation(buffer);
                }
        }
        
        //printf("total read : %d\n", total_num_read);
        buffer[total_num_read] = '\0';
        return buffer;
}



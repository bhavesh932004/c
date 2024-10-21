#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void assert_heap_allocation(void *p){
        assert(p != NULL);
}

char *read_line(FILE *file_p){
        int buffer_len = 32;
        char *buffer = (char *) malloc(buffer_len * sizeof(char));
        assert_heap_allocation(buffer);
        
        int total_num_read = 0;
        char *str;
        for(;;){
                buffer = fgets(buffer + total_num_read, buffer_len - total_num_read, file_p);
                if(buffer == NULL){
                        break;
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
                        buffer = realloc(buffer, 2 * buffer_len);
                        assert_heap_allocation(buffer);
                }
        }
        
        //printf("total read : %d\n", total_num_read);
        if(buffer != NULL){
                buffer[total_num_read] = '\0';
        }
        return buffer;
}


int main(int argc, char **argv){
        if(argc != 2){
                fprintf(stdout, "Usage : %s filename\n", argv[0]);
                exit(1);
        }

        FILE *file;
        
        file = fopen(argv[1], "r");
        if(file == NULL){
                fprintf(stdout, "Failed to open %s\n", argv[1]);
                exit(1);
        }
        
        for(;;){
                char *line = read_line(file);
                int len = strlen(line);
                if(len)
                        fprintf(stdout, "%s\n", line);
                free(line);

                if(len == 0){
                        break;
                }
        }

        fclose(file);

        return 0;
}


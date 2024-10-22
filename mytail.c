#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"read_line.h"

void mytail(FILE *file_p, const int N){
        char *lines[N];
        int i = 0;
        for(int i = 0; i < N; i++){
                lines[i] = NULL;
        }

        for(;;){
                char *line = read_line(file_p);
                if(line == NULL){
                        break;
                }
                
                if(lines[i] != NULL){
                        free(lines[i]);
                }

                int len = strlen(line);
                lines[i] = (char *) malloc(len + 1);
                strncpy(lines[i], line, len + 1);
                free(line);

                i = (i + 1) % N;
        }
        
        for(int j = 0; j < N; j++){
                if(lines[i] != NULL){
                        fprintf(stdout, "%s\n", lines[i]);
                        free(lines[i]);
                }
                i = (i + 1) % N;
        }
}

int main(int argc, char **argv){
        if(argc != 3){
                fprintf(stdout, "Usage: %s <filepath> <no of lines>\n", argv[0]);
                exit(1);
        }

        FILE *file;
        file = fopen(argv[1], "r");
        if(file == NULL){
                fprintf(stdout, "%s: no such file\n", argv[1]);
                exit(1);
        }

        mytail(file, atoi(argv[2])); 

        fclose(file);
}


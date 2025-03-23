#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "c_strtok.h"

const char *get_env_value(const char **envp, const char *key){
        for(int i = 0; envp[i] != NULL; i++){
                int env_key_len = 0;
                while(envp[i][env_key_len] != '='){
                        env_key_len++;
                }

                char env_key[env_key_len + 1];
                for(int j = 0; j < env_key_len; j++){
                        env_key[j] = envp[i][j];
                }
                env_key[env_key_len] = '\0';
                
                if(strncmp(key, env_key, env_key_len + 1) == 0){
                        return &envp[i][env_key_len + 1];
                }
        }

        return NULL;
}

void search_command(const char *env_path, char *command){
        for(;;){
                char *token = scan_token_alloc_buf(&env_path, ":");
                //fprintf(stdout, "TOKEN: %s\n", token);
                if(token == NULL)
                        break;
                
                size_t token_len = strlen(token);
                size_t cmd_len = strlen(command);
                char *cmd_path = (char *) malloc((token_len + cmd_len + 2) * sizeof(char));
                bool is_the_path = false;

                strncpy(cmd_path, token, token_len);
                cmd_path[token_len] = '/';
                strncpy(cmd_path + token_len + 1, command, cmd_len);
                cmd_path[token_len + cmd_len + 1] = '\0';
                
                if(access((const char *) cmd_path, F_OK & R_OK & X_OK) == 0){
                        fprintf(stdout, "%s\n", cmd_path);
                        is_the_path = true;
                }

                free(token);
                free(cmd_path);
                if(is_the_path)
                        break;
        }
}

int main(int argc, char **argv, const char **envp)
{
        const char *env_path = get_env_value(envp, "PATH");
        if(env_path == NULL){
                exit(1);
        }

        for(int i = 1; i < argc; i++){
                //fprintf(stdout, "COMMAND: %s\n", argv[i]);
                search_command(env_path, argv[i]);
        }

        return 0;
}

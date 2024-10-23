#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char **argv, const char **envp){
        if(argc != 2){
                fprintf(stdout, "Usage: %s <environment variable key>\n", argv[0]);
                exit(1);
        }
        
        const char *env_value = get_env_value(envp, argv[1]);
        printf("%s\n", env_value == NULL ? "" : env_value);
        return 0;
}


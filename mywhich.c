#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void merge(char *a, int left, int mid, int right){
	int n = mid - left + 1, m = right - mid;
	char L[n], R[m];

	for(size_t i = 0; i < n; i++){
		L[i] = a[left + i];
	}

	for(size_t i = 0; i < m; i++){
		R[i] = a[mid + 1 + i];
	}

	int i = 0, j = 0, k = 0;
	while(i < n || j < m){
		if(j >= m || (i < n && L[i] < R[j])){
			a[left + k++] = L[i++];
		}else{
			a[left + k++] = R[j++];
		}
	}
}

void merge_sort(char *a, int l, int r){
	if(l >= r){
		return;
	}

	int m = l + (r - l) / 2;
	merge_sort(a, l, m);
	merge_sort(a, m + 1, r);

	merge(a, l, m, r);
}

int b_search(char s[], char c){
	int l = 0, r = strlen(s) - 1;
	
	while(l <= r){
		int m = l + (r - l) / 2;
		if(s[m] == c){
			return m;
		}else if(s[m] < c){
			l = m + 1;
		}else{
			r = m - 1;
		}
	}

	return -1;	
}

size_t c_strspn(const char *s, const char *accept){
	int n = strlen(accept);
	char other[n + 1];
	strcpy(other, accept);

	merge_sort(other, 0, n - 1);

	size_t length = 0, s_len = strlen(s);
	for(size_t i = 0; i < s_len; i++){
		if(b_search(other, s[i]) == -1){
			break;
		}
		length++;
	}

	return length;
}

size_t c_strcspn(const char *s, const char *reject){
	int n = strlen(reject);
	char other[n + 1];
	strcpy(other, reject);

	merge_sort(other, 0, n - 1);

	size_t length = 0, s_len = strlen(s);
	for(size_t i = 0; i < s_len; i++){
		if(b_search(other, s[i]) != -1){
			break;
		}
		length++;
	}

	return length;
}

bool scan_token(const char **p_input, const char *delimiters, char buf[], size_t buflen)
{
	int n = strlen(delimiters);
	char other[n + 1];
	strcpy(other, delimiters);
	merge_sort(other, 0, n - 1);
        
        const char *input = *p_input;
        int start = 0;
        while(input[start] != '\0' && b_search(other, input[start]) != -1){
                start++;
        }

        int end = start;
        while(end - start < buflen - 1 && input[end] != '\0' && b_search(other, input[end]) == -1){
                end++;
        }

        for(int i = 0; i < end - start; i++){
                buf[i] = input[start + i];
        }
        
        *p_input = *p_input + end + (input[end] != '\0' && b_search(other, input[end]) != -1);
        
        buf[end - start] = '\0';
        return end - start > 0 ? true : false;
}

char *scan_token_n(const char **p_input, const char *delimiters)
{
	int n = strlen(delimiters);
	char other[n + 1];
	strcpy(other, delimiters);
	merge_sort(other, 0, n - 1);
        
        const char *input = *p_input;
        int start = 0;
        while(input[start] != '\0' && b_search(other, input[start]) != -1){
                start++;
        }

        int end = start;
        while(input[end] != '\0' && b_search(other, input[end]) == -1){
                end++;
        }
        
        if(end - start == 0)
                return NULL;

        char *token = (char *) malloc((end - start + 1) * sizeof(char));
        for(int i = 0; i < end - start; i++){
                token[i] = input[start + i];
        }
        token[end - start] = '\0';

        *p_input = *p_input + end + (input[end] != '\0');

        return token;
}

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
                char *token = scan_token_n(&env_path, ":");
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

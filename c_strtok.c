#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

bool scan_token_input_buf(const char **p_input, const char *delimiters, char buf[], size_t buflen)
{
	int n = strlen(delimiters);
	char other[n + 1];
	strncpy(other, delimiters, n + 1);
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

char *scan_token_alloc_buf(const char **p_input, const char *delimiters)
{
	int n = strlen(delimiters);
	char other[n + 1];
	strncpy(other, delimiters, n + 1);
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
	fprintf(stdout, "malloced\n");
        for(int i = 0; i < end - start; i++){
                token[i] = input[start + i];
        }
        token[end - start] = '\0';

        *p_input = *p_input + end + (input[end] != '\0');

        return token;
}

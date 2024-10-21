#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
int main(int argc, char *argv[]){
	void a = 10;
	printf("%d\n", (int)a);
	return 0;
}

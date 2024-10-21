void split(int *oa, int *la, int *ra, int start, int mid, int end){
	for(int i = start; i <= end; i++){
		if(i > mid){
			ra[i - mid - 1] = oa[i];
		}else{
			la[i - start] = oa[i];
		}
	}
}

void merge(int *la, int *ra, int la_len, int ra_len, int start, int *oa){
	int k = 0, i = 0, j = 0;
	while(i < la_len || j < ra_len){
		if(j >= ra_len || (i < la_len && la[i] <= ra[j])){
			oa[start + k] = la[i++];
		}else{
			oa[start + k] = ra[j++];
		}
		k++;
	}
}

void sort(int *oa, int start, int end){
	if(end - start == 0){
		return;
	}

	int mid = start + (end - start) / 2;
	sort(oa, start, mid);
	sort(oa, mid + 1, end);

	int la_len = mid - start + 1, ra_len = end - mid;
	int la[la_len], ra[ra_len];
	split(oa, la, ra, start, mid, end);

	merge(la, ra, la_len, ra_len, start, oa);
}

void mergesort(int *ia, int *oa, int len){
	for(int i = 0; i < len; i++){
		oa[i] = ia[i];
	}

	sort(oa, 0, len - 1);
}	

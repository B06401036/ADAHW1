#include <stdio.h>
#include <stdlib.h>
#define MAX 600000
int A[MAX] = {0};
int max_array[MAX] = {0};
int min_array[MAX] = {0};
int counter[MAX*2] = {0};
long long int sum = 0;
void l_max_min_array(int l, int m){
	max_array[m] = A[m];
	min_array[m] = A[m];
	for(int i = m-1; i >= l; i--){
		if(A[i] > max_array[i+1])
			max_array[i] = A[i];
		else 
			max_array[i] = max_array[i+1];
		if(A[i] < min_array[i+1])
			min_array[i] = A[i];
		else 
			min_array[i] = min_array[i+1];
	}
}
void r_max_min_array(int m, int r){
	max_array[m+1] =  A[m+1];
	min_array[m+1] = A[m+1];
	for(int i = m+2; i <= r; i++){
		if(A[i] > max_array[i-1])
			max_array[i] = A[i];
		else 
			max_array[i] = max_array[i-1];
		if(A[i] < min_array[i-1])
			min_array[i] = A[i];
		else 
			min_array[i] = min_array[i-1];
	}
}
long long l_max_r_min(int l, int m, int r){
	int r_legal, l_legal;
	long long count = 0;
	r_legal = m + 1;
	l_legal = m + 1;
	//l + max = r + min
	for(int i = m; i >= l; i--){
		while(r_legal <= r && max_array[r_legal] < max_array[i]){
			// counter[min + r] counts how many min+r occur
			counter[r_legal + min_array[r_legal]]++;
			r_legal++;
		}
		while(l_legal <= r && min_array[l_legal] > min_array[i]){
			counter[l_legal + min_array[l_legal]]--;
			l_legal++;
		}
		//l + max
		if(counter[i + max_array[i]] > 0) 
			count += counter[i + max_array[i]];
	}
	//clear counter array
	for(int i = m+1; i <= r; i++){
		counter[min_array[i] + i] = 0;
	}
	//printf("l_max_r_min %lld\n", count);
	return count;
}
long long r_max_l_min(int l, int m, int r){
	long long count = 0;
	int r_legal, l_legal;
	r_legal = m;
	l_legal = m;
	//l + max = r + min
	//max - r = min - l
	for(int i = m+1; i <= r; i++){
		//printf("precount %lld\n", count);
		while(l_legal >= l && max_array[l_legal] < max_array[i]){
			// counter[l-min] counts how many min+r occur
			// noted that l-min may be negative
			counter[MAX - (min_array[l_legal] - l_legal)]++;
			l_legal--;
		}
		//合法左界的右界
		while(r_legal >= l && min_array[r_legal] > min_array[i]){
			// count l + max occur
			counter[MAX - (min_array[r_legal] - r_legal)]--;
			r_legal--;
		}
		//l + max
		int value = max_array[i]-i;
		if(counter[MAX-value] > 0){
			count += counter[MAX-value];
		}
	}
	//clear counter array
	for(int i = m; i >= l; i--){
		counter[MAX - (min_array[i] - i)] = 0;
	}
	return count;
}
long long l_max_l_min(int l, int m, int r){
	long long count = 0;
	for(int i = m; i >= l; i--){
		//gap presents how many numbers 
		int gap = max_array[i] - min_array[i];
		//if cross the middle line and the numbers are between max and min
		if(gap + i > m && gap + i <= r &&max_array[gap+i] < max_array[i] && min_array[gap+i] > min_array[i]){
				count++;
		}
	}
	return count;
}
long long r_max_r_min(int l, int m, int r){
	long long count = 0;
	for(int i = m+1; i <= r; i++){
		int gap = max_array[i] - min_array[i];
		if(i - gap <= m && i - gap >= l && max_array[i-gap] < max_array[i] && min_array[i-gap] > min_array[i]){
				count++;
		}
	}
	return count;
}
void good_subpermutation(int l, int r){
	if(l==r){
		sum++;
		return;
	}
	int m = (l+r)/2;
	good_subpermutation(l, m);
	good_subpermutation(m+1, r);
	
	l_max_min_array(l, m);
	r_max_min_array(m, r);
	sum += l_max_r_min(l, m, r);
	sum += r_max_l_min(l, m ,r);
	sum += l_max_l_min(l, m, r);
	sum += r_max_r_min(l, m ,r);
	return;
}
int main(){
	int N = 0;
	scanf("%d ", &N);
	for(int i = 0; i < N; i++){
		scanf("%d", &A[i]);
	}
	good_subpermutation(0, N-1);
	printf("%lld\n", sum);
	return 0;
}
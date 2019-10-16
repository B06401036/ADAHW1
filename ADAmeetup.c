#include <stdio.h>
#define MAX 1000000000
long long int sum = 0;
void merge(int p[], int s_bound[], int l_bound[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1, n2 = r - m;
	int l_p[n1], l_s_bound[n1], l_l_bound[n1];
	int r_p[n2], r_s_bound[n2], r_l_bound[n2];
	for(i = l; i <= m; i++){
		l_p[i-l] = p[i];
		l_s_bound[i-l] = s_bound[i];
		l_l_bound[i-l] = l_bound[i];
	}
	for(i = m+1; i <= r; i++){
		r_p[i-m-1] = p[i];
		r_s_bound[i-m-1] = s_bound[i];
		r_l_bound[i-m-1] = l_bound[i];
	}
	long long int s_bound_sum = 0, l_bound_sum = 0;	
    i = j = 0;
    //check small(lower) bound
	while(i < n1 && j < n2){
		if(r_s_bound[j] <= l_p[i]){
			s_bound_sum += i;
			j++;
		}
		else i++;

	}
	while(j < n2){
		s_bound_sum += n1;
		j++;
	}
	//check large(upper) bound
	i = j = 0;
	while(i < n1 && j < n2){
		if(r_l_bound[j] >= l_p[i] && (r_l_bound[j] < l_p[i+1] || i== n1-1)){
			l_bound_sum += i+1;
			j++;
		}
		else if(r_l_bound[j] < l_p[i]){
			j++;
		}
		else i++;
	}
	if(j < n2){
		l_bound_sum += n1;
		j++;
	}
	sum += l_bound_sum - s_bound_sum;
	//merge all the arrays
	i = j = 0;
	k = l;
	while (i < n1 && j < n2) { 
        if(l_p[i] <= r_p[j]){ 
            p[k] = l_p[i]; 
            i++; 
        } 
        else{ 
            p[k] = r_p[j]; 
            j++; 
        } 
        k++; 
    }
    while(i < n1){
    	p[k] = l_p[i];
    	i++;
    	k++;
    }
    while(j < n2){
    	p[k] = r_p[j];
    	j++;
    	k++;
    }
    i = j = 0;
	k = l;
	while (i < n1 && j < n2) { 
        if(l_s_bound[i] <= r_s_bound[j]){ 
            s_bound[k] = l_s_bound[i]; 
            i++; 
        } 
        else{ 
            s_bound[k] = r_s_bound[j]; 
            j++; 
        } 
        k++; 
    }
    while(i < n1){
    	s_bound[k] = l_s_bound[i];
    	i++;
    	k++;
    }
    while(j < n2){
    	s_bound[k] = r_s_bound[j];
    	j++;
    	k++;
    }
    i = j = 0;
	k = l;
	while (i < n1 && j < n2) { 
        if(l_l_bound[i] <= r_l_bound[j]){ 
            l_bound[k] = l_l_bound[i]; 
            i++; 
        } 
        else{ 
            l_bound[k] = r_l_bound[j]; 
            j++; 
        } 
        k++; 
    }
    while(i < n1){
    	l_bound[k] = l_l_bound[i];
    	i++;
    	k++;
    }
    while(j < n2){
    	l_bound[k] = r_l_bound[j];
    	j++;
    	k++;
    }	
    return;
}
void mergesort(int p[], int s_bound[], int l_bound[], int l, int r){
	if(l < r){
		int m = (l+r)/2;
		mergesort(p, s_bound, l_bound, l, m);
		mergesort(p, s_bound, l_bound, m+1, r);
		merge(p, s_bound, l_bound, l, m, r);
	}
}
int main(){
	int N;
	scanf("%d", &N);
	int p[N], s_bound[N], l_bound[N];
	for(int i = 0; i < N; i++){
		scanf("%d", &p[i]);
	}
	int f;
	for(int i = 0; i < N; i++){
		scanf("%d", &f);
		s_bound[i] = (p[i] - f < 0)?0:p[i]-f;
		l_bound[i] = (p[i] + f > MAX)? MAX: p[i]+f;
	}
	mergesort(p, s_bound, l_bound, 0, N-1);
	printf("%lld\n", sum);
	return 0;
}
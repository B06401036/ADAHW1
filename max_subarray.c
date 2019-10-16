#include <stdio.h>
#include <stdlib.h> 
#define treeMAX 3000000
#define max(a,b) ((a>=b)?a:b)
typedef struct node{
	long long prefix;
	long long suffix;
	long long sum;
	long long maxsum;
}Node;
//use array to build the tree
Node S[treeMAX];
void build_maxarray_tree(int *A, int l, int r, int node_index){
	if(l == r){
		S[node_index].prefix = A[l];
		S[node_index].suffix = A[l];
		S[node_index].sum = A[l];
		S[node_index].maxsum = A[l];
		return;
	}
	int m = (l+r)/2;
	int l_ch_index = 2*node_index+1, r_ch_index = 2*node_index +2;
	//left_child
	build_maxarray_tree(A, l, m, l_ch_index);
	//right_child
	build_maxarray_tree(A, m+1, r, r_ch_index);
	//parent
	S[node_index].prefix = max(S[l_ch_index].prefix, S[l_ch_index].sum + S[r_ch_index].prefix);
	S[node_index].suffix = max(S[r_ch_index].suffix, S[l_ch_index].suffix + S[r_ch_index].sum);
	S[node_index].sum = S[l_ch_index].sum + S[r_ch_index].sum;
	S[node_index].maxsum = max(S[node_index].prefix, max(S[node_index].suffix, max(S[l_ch_index].maxsum, max(S[r_ch_index].maxsum, S[l_ch_index].suffix + S[r_ch_index].prefix))));
	return; 
}
void modify(int *A, int l, int r, int node_index, int update_p, int update_v){
	//find the leaf node
	if(l == r){
		S[node_index].prefix = update_v;
		S[node_index].suffix = update_v;
		S[node_index].sum = update_v;
		S[node_index].maxsum = update_v;
		return;
	}
	int m = (l+r)/2;
	int l_ch_index = 2*node_index+1, r_ch_index = 2*node_index +2;
	//find which subtree contains update_p
	if(update_p <= m){
		modify(A, l, m, l_ch_index, update_p, update_v);
	}
	else{
		modify(A, m+1, r, r_ch_index, update_p, update_v);
	}
	S[node_index].prefix = max(S[l_ch_index].prefix, S[l_ch_index].sum + S[r_ch_index].prefix);
	S[node_index].suffix = max(S[r_ch_index].suffix, S[l_ch_index].suffix + S[r_ch_index].sum);
	S[node_index].sum = S[l_ch_index].sum + S[r_ch_index].sum;
	S[node_index].maxsum = max(S[node_index].prefix, max(S[node_index].suffix, max(S[l_ch_index].maxsum, max(S[r_ch_index].maxsum, S[l_ch_index].suffix + S[r_ch_index].prefix))));
	return;
}
int main(){
	int N, Q;
	scanf("%d %d", &N, &Q);
	int *A=(int*)malloc(sizeof(int)*N);
	for(int i = 0; i < N; i++){
		scanf("%d", &A[i]);
	}
	build_maxarray_tree(A, 0, N-1, 0);
	if(S -> maxsum < 0) printf("0\n");
	else printf("%lld\n", S -> maxsum);
	int p, v;
	for(int i = 0; i < Q; i++){
		scanf("%d %d", &p, &v);
		A[p-1] = v;
		modify(A, 0, N-1, 0, p-1, v);
		if(S -> maxsum < 0) printf("0\n");
		else printf("%lld\n", S -> maxsum);
	}
	return 0;
} 


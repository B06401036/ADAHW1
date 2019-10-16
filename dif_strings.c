#include <iostream>
#include <algorithm>
using namespace std;
int min(int a, int b, int c){
	return min(min(a,b), c);
}
int edit_distance(string s1, string s2, int m, int n){
	int matrix[m+1][n+1];
	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= n; j++){
			if(i == 0)
				matrix[i][j] = j;
			else if(j == 0)
				matrix[i][j] = i;
			else if(s1[i-1] != s2[j-1]){
				matrix[i][j] = matrix[i-1][j-1];
			}
			else{
				matrix[i][j] = 1+ min(matrix[i][j-1], matrix[i-1][j], matrix[i-1][j-1]);
			}
		}
	}
	/*for(int i = 0; i <= n; i++){
		for(int j = 0; j <= m; j++){
			cout << matrix[j][i] <<" ";
		}
		cout << endl;
	}*/
	int minimum = 2005;
	for(int i = m; i <= n; i++){
		for(int j = 0; j <= m; j++){
			if(matrix[j][i] < minimum) minimum = matrix[j][i];
		}
	}
	for(int i = 0; i <= m; i++){
		if(matrix[m][i] < minimum) minimum = matrix[m][i];
	}
	return minimum;
}
int main(){
	string s1, s2;
	cin >> s1 >> s2;
	int m = s1.length(), n = s2.length();
	//cout << s1 << endl << s2 << endl;
	if(m<n)cout << edit_distance(s1, s2, m, n) << endl;
	else cout << edit_distance(s2, s1, n, m) << endl;
	return 0;
}
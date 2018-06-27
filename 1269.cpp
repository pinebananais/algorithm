#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;

set<int> S;

int main(){
	int A, B;
	int inter_cnt = 0; // cardinality of intersection set
	scanf("%d %d", &A, &B);
	for(int i = 0, t; i < A; i++){
		scanf("%d", &t);
		S.insert(t);
	}
	for(int i = 0, t; i < B; i++){
		scanf("%d", &t);
		if(S.find(t) != S.end()) inter_cnt++;
	}
	printf("%d\n", A + B - 2 * inter_cnt);
}
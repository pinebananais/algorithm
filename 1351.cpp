#include <stdio.h>
#include <map>
#include <algorithm>

using namespace std;

map<long long int, long long int> DP;

long long int N, P, Q;

long long int dp(long long int idx){
	if(idx == 0) return 1;
	if(DP.find(idx) != DP.end()) return DP[idx];
	else DP[idx] = dp(idx / P) + dp(idx / Q);
}

int main(){
	scanf("%lld %lld %lld", &N, &P, &Q);
	printf("%lld\n", dp(N));
}
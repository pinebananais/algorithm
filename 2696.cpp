#include <stdio.h>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;


int main(){
	int test_case;
	scanf("%d", &test_case);
	while(test_case--){
		priority_queue<int> max_heap;
		priority_queue<int, vector<int>, greater<int> > min_heap;
		int mean;
		vector<int> ans;

		int N;
		scanf("%d", &N);
		for(int i = 0, t; i < N; i++){
			scanf("%d", &t);
			if(i == 0){
				mean = t;
				ans.push_back(mean);
				continue;
			}
			if(i % 2 == 0){
				int left = max_heap.top();
				int right = min_heap.top();
				if(t > right){
					mean = right;
					min_heap.pop();
					min_heap.push(t);
				}
				else if(t < left){
					mean = left;
					max_heap.pop();
					max_heap.push(t);
				}
				else{
					mean = t;
				}
				ans.push_back(mean);
			}
			else{
				if(t > mean){
					min_heap.push(t);
					max_heap.push(mean);
				}
				else{
					max_heap.push(t);
					min_heap.push(mean);
				}
			}
		}
		int size = ans.size();
		printf("%d", size);
		for(int i = 0; i < size; i++){
			if(i % 10 == 0) puts("");
			printf("%d ", ans[i]);
		}
		puts("");
	}
}
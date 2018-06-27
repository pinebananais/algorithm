// 최소 힙 1927

#include <stdio.h>

int heap[1 << 17];
int last_idx = 0; // index for last element
int temp_idx = 0; // temp index

int Peek(){ // return min element
	if(last_idx == 0) return 0;
	return heap[1];
}

void Insert(int key){
	heap[++last_idx] = key;
	temp_idx = last_idx;
	while(temp_idx > 1){
		if(heap[temp_idx] > heap[temp_idx / 2]) break;
		else{ // swap
			int temp = heap[temp_idx];
			heap[temp_idx] = heap[temp_idx / 2];
			heap[temp_idx / 2] = temp;
			temp_idx /= 2;
		}
	}
}

void Delete(){
	if(last_idx == 0) return;
	heap[1] = heap[last_idx--];
	temp_idx = 1;
	while(temp_idx <= last_idx / 2){
		if(heap[temp_idx] < heap[temp_idx * 2] && heap[temp_idx] < heap[temp_idx * 2 + 1]) break;
		if(heap[temp_idx * 2] < heap[temp_idx * 2 + 1]){
			int temp = heap[temp_idx];
			heap[temp_idx] = heap[temp_idx * 2];
			heap[temp_idx * 2] = temp;
			temp_idx *= 2;
		}
		else{
			int temp = heap[temp_idx];
			heap[temp_idx] = heap[temp_idx * 2 + 1];
			heap[temp_idx * 2 + 1] = temp;
			temp_idx = temp_idx * 2 + 1;
		}
	}
}

int main(){
	int N;
	scanf("%d", &N);

	for(int i = 0, t; i < N; i++){
		scanf("%d", &t);

		if(t > 0) Insert(t);
		else{
			printf("%d\n", Peek());
			Delete();
		}
	}

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define SZ 9
int ans[SZ][SZ];
int pre[SZ][SZ];

void print(){
	for(int i = 0; i < SZ; i++){
		for(int j = 0; j < SZ; j++){
			printf("%d ", ans[i][j]);
		}
		puts("");
	}
	exit(0);
}

bool valid(int r, int c, int num){
	for(int i = 0; i < SZ; i++){
		if(ans[r][i] == num) return false;
		if(ans[i][c] == num) return false;
		if(ans[(r/3)*3 + i/3][(c/3)*3 + i%3] == num) return false;
	}
	return true;
}

void sudoku(int r, int c){
	if(c == SZ) r++, c = 0;
	if(r == SZ){
		print();
		return;
	}
	if(pre[r][c]) return sudoku(r, c+1);
	for(int i = 1; i <= SZ; i++){
		if(valid(r, c, i)){
			ans[r][c] = i;
			sudoku(r, c+1);
			ans[r][c] = 0;
		}
	}
}

int main(){
	for(int i = 0; i < SZ; i++){
		for(int j = 0; j < SZ; j++){
			scanf("%d", &pre[i][j]);
			if(pre[i][j] != 0) ans[i][j] = pre[i][j];
		}
	}
	sudoku(0, 0);
}
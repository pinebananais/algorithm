#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLACK 0
#define LEFT 0
#define RIGHT 1
#define LEAF NULL

struct node{
	int key;
	int color;
	node *ch[2];
};

struct tree{
	node *root;
};

int color_of(node *N){
	if(N == LEAF) return BLACK;
	return N->color;
}

node* rotate(node *N, int dir){
	node *tmp = N->ch[!dir]->ch[dir];
	node *ret = N->ch[!dir];
	N->ch[!dir] = tmp;
	ret->ch[dir] = N;
	return ret;
}

node* create_node(int k){
	node *ret = (node*)malloc(sizeof(node));
	ret -> key = k;
	ret -> ch[LEFT] = ret -> ch[RIGHT] = NULL;
	ret -> color = RED;
	return ret;
}

node* search_node(node* N, int k){
	if(N == NULL) return NULL;
	if(N->key == k) return N;
	else if(N->key < k) return search_node(N->ch[RIGHT], k);
	else return search_node(N->ch[LEFT], k);
}

node* search_tree(tree* T, int k){
	if(T->root) return search_node(T->root, k);
	else NULL;
}

node* insert_node(node* N, node* X){
	if(N == NULL) return X;
	if(N->key < X->key){
		N->ch[RIGHT] = insert_node(N->ch[RIGHT], X);
		if(color_of(N->ch[RIGHT]) == RED && color_of(N->ch[RIGHT]->ch[LEFT]) == RED){
			if(color_of(N->ch[LEFT]) == RED){
				N->color = RED;
				N->ch[LEFT]->color = N->ch[RIGHT]->color = BLACK;
			}
			else{
				N->ch[RIGHT] = rotate(N->ch[RIGHT], RIGHT);
				N = rotate(N, LEFT);
				N->color = BLACK;
				N->ch[LEFT]->color = RED;
			}
		}
		else if(color_of(N->ch[RIGHT]) == RED && color_of(N->ch[RIGHT]->ch[RIGHT]) == RED){
			if(color_of(N->ch[LEFT]) == RED){
				N->color = RED;
				N->ch[LEFT]->color = N->ch[RIGHT]->color = BLACK;
			}
			else{
				N = rotate(N, LEFT);
				N->color = BLACK;
				N->ch[LEFT]->color = RED;
			}
		}
	}
	else{
		N->ch[LEFT] = insert_node(N->ch[LEFT], X);
		if(color_of(N->ch[LEFT]) == RED && color_of(N->ch[LEFT]->ch[RIGHT]) == RED){
			if(color_of(N->ch[RIGHT]) == RED){
				N->color = RED;
				N->ch[RIGHT]->color = N->ch[LEFT]->color = BLACK;
			}
			else{
				N->ch[LEFT] = rotate(N->ch[LEFT], LEFT);
				N = rotate(N, RIGHT);
				N->color = BLACK;
				N->ch[RIGHT]->color = RED;
			}
		}
		else if(color_of(N->ch[LEFT]) == RED && color_of(N->ch[LEFT]->ch[LEFT]) == RED){
			if(color_of(N->ch[RIGHT]) == RED){
				N->color = RED;
				N->ch[RIGHT]->color = N->ch[LEFT]->color = BLACK;
			}
			else{
				N = rotate(N, RIGHT);
				N->color = BLACK;
				N->ch[RIGHT]->color = RED;
			}
		}
	}
	return N;
}

void insert_tree(tree *T, int k){
	node *new_node = create_node(k);
	T->root = insert_node(T->root, new_node);
	T->root->color = BLACK;
}

node* delete_node(node *N, int k){
	if(N == NULL) return NULL;
	if(N->key == k){
		node *tmp = N;
		if(N->ch[RIGHT] == NULL) tmp = N->ch[LEFT];
		else if(N->ch[LEFT] == NULL) tmp = N->ch[RIGHT];
		else{
			tmp = N->ch[RIGHT];
			while(tmp->ch[LEFT]) tmp = tmp->ch[LEFT];
			N->key = tmp->key;
			N->ch[RIGHT] = delete_node(N->ch[RIGHT], N->key);
			return N;
		}
		free(N);
		return tmp;
	}
	else if(N->key < k) N->ch[RIGHT] = delete_node(N->ch[RIGHT], k);
	else N->ch[LEFT] = delete_node(N->ch[LEFT], k);
	return N;
}

void delete_tree(tree *T, int k){
	T->root = delete_node(T->root, k);
}

void print_node(node* N){
	if(N == NULL) return;
	print_node(N->ch[LEFT]);
	printf("%d ", N->key);
	print_node(N->ch[RIGHT]);
}

void print_tree(tree *T){
	node* Q[1000];
	int level[1000];
	int idx = 0;
	int fr = 0, rr = -1;
	Q[++rr] = T->root;
	level[rr] = 0;
	while(rr >= fr){
		int lev = level[fr];
		if(lev > idx){
			idx = lev;
			puts("");
		}
		node *x = Q[fr++];
		if(x == NULL){
			printf("NIL ");
			continue;
		}
		printf("%d%s ", x->key, (x->color == RED)? "RED":"BLACK");
		Q[++rr] = x->ch[LEFT];
		level[rr] = lev + 1;
		Q[++rr] = x->ch[RIGHT];
		level[rr] = lev + 1;

	}
	puts("");
}

int main(){
	tree* T = (tree*)malloc(sizeof(tree));
	T->root = NULL;
	insert_tree(T, 4);
	insert_tree(T, 6);
	insert_tree(T, 3);
	insert_tree(T, 7);
	insert_tree(T, 9);
	insert_tree(T, 1);
	insert_tree(T, 2);
	print_tree(T);
}
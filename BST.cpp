#include <stdio.h>
#include <stdlib.h>

struct node{
	int key;
	node *left, *right;
};

struct tree{
	node *root;
};

node* create_node(int k){
	node *ret = (node*)malloc(sizeof(node));
	ret -> key = k;
	ret ->left = ret -> right = NULL;
	return ret;
}

node* search_node(node* N, int k){
	if(N == NULL) return NULL;
	if(N->key == k) return N;
	else if(N->key < k) return search_node(N->right, k);
	else return search_node(N->left, k);
}

node* search_tree(tree* T, int k){
	if(T->root) return search_node(T->root, k);
	else NULL;
}

node* insert_node(node* N, node* X){
	if(N == NULL) return X;
	else if(N->key < X->key) N->right = insert_node(N->right, X);
	else N->left = insert_node(N->left, X);
	return N;
}

void insert_tree(tree *T, int k){
	node *new_node = create_node(k);
	T->root = insert_node(T->root, new_node);
}

node* delete_node(node *N, int k){
	if(N == NULL) return NULL;
	if(N->key == k){
		node *tmp = N;
		if(N->right == NULL) tmp = N->left;
		else if(N->left == NULL) tmp = N->right;
		else{
			tmp = N->right;
			while(tmp->left) tmp = tmp->left;
			N->key = tmp->key;
			N->right = delete_node(N->right, N->key);
			return N;
		}
		free(N);
		return tmp;
	}
	else if(N->key < k) N->right = delete_node(N->right, k);
	else N->left = delete_node(N->left, k);
	return N;
}

void delete_tree(tree *T, int k){
	T->root = delete_node(T->root, k);
}

void print_node(node* N){
	if(N == NULL) return;
	print_node(N->left);
	printf("%d ", N->key);
	print_node(N->right);
}

void print_tree(tree *T){
	print_node(T->root);
	puts("");
}

int main(){
	tree* T = (tree*)malloc(sizeof(tree));
	T->root = NULL;
	insert_tree(T, 4);
	insert_tree(T, 6);
	insert_tree(T, 3);
	insert_tree(T, 7);
	print_tree(T);
	delete_tree(T, 4);
	print_tree(T);
	delete_tree(T, 3);
	print_tree(T);
	delete_tree(T, 7);
	print_tree(T);
}
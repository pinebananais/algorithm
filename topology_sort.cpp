#include <stdio.h>
#include <vector>
#include <algorithm>
#define MAXV 500050
using namespace std;

/**************************
Given a directed graph and output whether it contains
a directed cycle or not. If no, also output topological order of DAG.

Given G = (V, E),
Let:
N := |V|
M := |E|
indeg[i] := Indegree of i'th vertex
adj[i] := Adjacency list of i'th vertex
topol[i] := i'th vertex in topological order

**************************/

int N, M;
int indeg[MAXV];
vector<int> adj[MAXV];
vector<int>::iterator it;
int topol[MAXV];
int idx = 0; // index of topol array

int Q[MAXV];
int rr = -1, fr = 0;

int main(){
	//uncomment for file input/output
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d %d", &N, &M);
	for(int i = 0, u, v; i < M; i++){
		scanf("%d %d", &u, &v); // edge that u -> v
		adj[u].push_back(v);
		indeg[v]++;
	}
	for(int i = 0; i < N; i++){
		if(indeg[i] == 0) Q[++rr] = i; // Inqueue vertices which of indegree is zero.
	}

	while(rr >= fr){
		int cur = Q[fr++];
		topol[idx++] = cur; // Dequeue and store to topol array
		int size = adj[cur].size();
		for(int i = 0; i < size; i++){
			int next = adj[cur][i]; // All vertices adjacent to current vertex
			if(--indeg[next] == 0) Q[++rr] = next; // Decrease indegree since current vertex is erased
		}
	}

	if(idx == N){ // If every vertex contained in topol array
		puts("no"); // There is no directed cycle
		for(int i = 0; i < N; i++) printf("%d ", topol[i]);
		puts("");
	}
	else{
		puts("yes");
	}
}
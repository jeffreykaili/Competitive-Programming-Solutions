#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f3f3f3f3f 
const int MM = 5e5+3; 
int n, sz[MM], level[MM], above[MM]; long long dist[20][MM], Mdist[MM]; vector<pair<int, int>> graph[MM]; bool blocked[MM]; 
void getsz(int node, int par) {
	sz[node] = 1; 
	for(auto&[u, w] : graph[node]) {
		if(u == par || blocked[u]) continue; 
		getsz(u, node); 
		sz[node] += sz[u]; 
	}
}
int centroid(int node, int par, int SIZE) {
	for(auto&[u, w] : graph[node]) {
		if(u == par || blocked[u]) continue;
		if(sz[u] > SIZE/2) return centroid(u, node, SIZE); 
	}
	return node; 
}
void calc(int node, int par, long long len, int lvl) {
	dist[lvl][node] = len; 
	for(auto&[u, w] : graph[node]) {
		if(u == par || blocked[u]) continue; 
		calc(u, node, len + w, lvl); 
	}
}	
void decomp(int root, int par, int lvl) {
	getsz(root, -1); 
	int cent = centroid(root, -1, sz[root]); 
	level[cent] = lvl; above[cent] = par; 
	calc(cent, par, 0, lvl); 
	blocked[cent]=1; 
	for(auto&[u, w] : graph[cent]) {
		if(u == par || blocked[u]) continue; 
		decomp(u, cent, lvl+1); 
	}
}
void Init(int N, int A[], int B[], int D[]) {
	n = N; 
	for(int i=0; i<n-1; i++) {
		graph[A[i]].push_back({B[i], D[i]}); 
		graph[B[i]].push_back({A[i], D[i]}); 
	}
	decomp(0, -1, 0); 
	memset(Mdist, 0x3f, sizeof(Mdist)); 
}

long long Query(int S, int X[], int T, int Y[]) {
	long long ans = inf; 
	vector<int> reset; 
	for(int i=0; i<S; i++) {
		// rebuilding length 
		int nd = X[i]; 
		while(nd != -1) {
			reset.push_back(nd); 
			Mdist[nd] = min(Mdist[nd], dist[level[nd]][X[i]]); 
			nd = above[nd]; 
		}
	}
	for(int i=0; i<T; i++) {
		// query now 
		int nd = Y[i]; 
		while(nd != -1) {
			reset.push_back(nd); 
			ans = min(ans, Mdist[nd] + dist[level[nd]][Y[i]]); 
			nd = above[nd]; 
		}
	}
	for(int x : reset) Mdist[x] = inf; 
	return ans; 
}

int main() {
	return 0; 
}
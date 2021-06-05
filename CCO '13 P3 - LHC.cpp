#include <bits/stdc++.h>
using namespace std;
const int MM = 4e5+3; 
int n, sz[MM], dia; long long ans; bool blocked[MM]; 
vector<int> graph[MM]; map<int, int> len; 
void getsz(int node, int par) {
	sz[node]=1; 
	for(int u : graph[node]) {
		if(u == par || blocked[u]) continue; 
		getsz(u, node); 
		sz[node] += sz[u]; 
	}
}
int centroid(int node, int par, int N) {
	for(int u : graph[node]) {
		if(u == par || blocked[u]) continue; 
		if(sz[u] > N/2) return centroid(u, node, N); 
	}
	return node; 
}
void dfs(int node, int par, int length, vector<int>& path) {
	path.push_back(length); 
	if(length + len.rbegin()->first > dia) {
		dia = length + len.rbegin()->first; 
		ans = len.rbegin()->second; 
	} else if (length + len.rbegin()->first == dia) ans += len.rbegin()->second;
	for(int u : graph[node]) {
		if(u == par || blocked[u]) continue; 
		dfs(u, node, length+1, path); 
	}
}
void decomp(int root) {
	getsz(root, -1); 
	int cent = centroid(root, -1, sz[root]); 
	len.clear(); len[0]=1; 
	for(int u : graph[cent]) {
		if(blocked[u]) continue; 
		vector<int> path; 
		dfs(u, cent, 1, path); 
		for(int x : path) len[x]++; 
	}
	blocked[cent]=1; 
	for(int u : graph[cent]) 
		if(!blocked[u]) decomp(u); 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin>>n; 
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y; 
		graph[x].push_back(y); 
		graph[y].push_back(x); 
	}
	decomp(1); 
	cout << dia+1 << " " << ans << '\n'; 
}
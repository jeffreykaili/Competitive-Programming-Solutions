#include <bits/stdc++.h>
using namespace std;
const int MM = 1e5+3; 
int n, sz[MM]; long long ans; char c; bool blocked[MM];  
vector<pair<int, int>> graph[MM]; map<int, int> freq;  
void dfs1(int node, int par) {
	sz[node]=1; 
	for(auto&[u, c] : graph[node]) {
		if(blocked[u] || u==par) continue; 
		dfs1(u, node); 
		sz[node] += sz[u]; 
	}
}
int centroid(int node, int par, int N) {
	for(auto&[u, c] : graph[node]) {
		if(blocked[u] || u==par) continue; 
		if(sz[u] > N/2) return centroid(u, node, N);   
	} // if all children have size <= N/2 
	return node; 
}
void dfs2(int node, int par, int weight, vector<int>& len) {
	// how many with path length + 1 and -1 
	ans += freq[-weight-1]; ans += freq[-weight+1];
	len.push_back(weight);
	for(auto&[u, c] : graph[node]) {
		if(blocked[u] || u==par) continue; 
		dfs2(u, node, weight+c, len); 
	} 
}
void dac(int root) {
	dfs1(root, -1); 
	int cent = centroid(root, -1, sz[root]); 
	freq.clear(); freq[0]=1; 
	for(auto&[u, c] : graph[cent]) {
		if(blocked[u]) continue; 
		vector<int> len; // path lengths 
		dfs2(u, cent, c, len); 
		for(int x : len) freq[x]++; 
	}
	blocked[cent]=1; 
	for(auto&[u, c] : graph[cent]) 
		if(!blocked[u]) dac(u); 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin>>n; 
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y>>c; 
		graph[x].push_back({y, (c=='r'?1:-1)}); 
		graph[y].push_back({x, (c=='r'?1:-1)}); 
	}
	dac(1); 
	cout << ans - n + 1 << '\n'; 
}
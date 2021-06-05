#include <bits/stdc++.h>
using namespace std;
const int MM = 2e5+3, MX = 1e6; 
int n, k, sz[MM], ans=INT_MAX, iter; bool blocked[MM]; 
vector<pair<int, int>> graph[MM]; 
pair<int, int> freq[2*MX+3]; 
void getsz(int node, int par) {
	sz[node]=1; 
	for(auto&[u, c] : graph[node]) {
		if(blocked[u] || u==par) continue; 
		getsz(u, node); 
		sz[node]+=sz[u]; 
	}
}
int centroid(int node, int par, int N) {
	for(auto&[u, c] : graph[node]) {
		if(blocked[u] || u==par) continue; 
		if(sz[u] > N/2) return centroid(u, node, N); 
	}
	return node; 
}
void dfs(int node, int par, int length, int edges, map<int, int>& len) {
	if((freq[k-length].first && freq[k-length].second == iter) || k-length == 0) ans = min(ans, edges + freq[k-length].first);
	len[length]=(len[length]==0?edges:min(len[length], edges));
	for(auto&[u, c] : graph[node]) {
		if(blocked[u] || u==par || length+c>k) continue; 
		dfs(u, node, length+c, edges+1, len); 
	}
}
void dac(int root) {
	getsz(root, -1); 
	int cent = centroid(root, -1, sz[root]); 	
	for(auto&[u, c] : graph[cent]) {
		if(blocked[u] || c > k) continue; 
		map<int, int> len; 
		dfs(u, cent, c, 1, len); 
		for(auto&[l, v] : len) {
			if(freq[l].second == iter && freq[l].first) freq[l] = min(freq[l], {v, iter}); 
			else freq[l]={v, iter};
		}
	}
	blocked[cent]=1; 
	for(auto&[u, c] : graph[cent])
		if(!blocked[u]) iter++, dac(u); 
}	
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin>>n>>k; 
	for(int i=1,x,y,w;i<n;i++) {
		cin>>x>>y>>w; 
		graph[x].push_back({y, w}); 
		graph[y].push_back({x, w}); 
	}
	dac(1); 
	if(ans==INT_MAX) cout << -1 << '\n'; 
	else cout << ans << '\n'; 
}
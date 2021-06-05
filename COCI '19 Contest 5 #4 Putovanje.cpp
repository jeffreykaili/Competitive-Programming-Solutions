#include <bits/stdc++.h>
using namespace std;
const int MM = 2e5+3; 
struct edge{int y, a, b;}; 
int n, depth[MM], up[20][MM]; long long diff[MM], ans; 
vector<edge> graph[MM]; 
void dfs(int node, int par) {
	for(auto&[u,a,b] : graph[node]) {
		if(u == par) continue; 
		depth[u] = depth[node] + 1; 
		up[0][u] = node; 
		for(int i=1;i<19;i++) up[i][u] = up[i-1][up[i-1][u]]; 
 		dfs(u, node); 
 	} 
}
int qlca(int a, int b) {
	if(depth[a] < depth[b]) swap(a, b); 
	int k = depth[a] - depth[b]; 
	for(int j=19; j>=0; j--) 
		if(k >= (1<<j)) a = up[j][a], k -= (1<<j); 
	if(a==b) return a; 
	for(int j=19; j>=0; j--) 
		if(up[j][a] != up[j][b]) 
			a = up[j][a], b = up[j][b]; 
	return up[0][a]; 
}
void pd(int node, int par) {
	for(auto&[u,a,b] : graph[node]) {
		if(u == par) continue; 
		pd(u, node); 
		diff[node] += diff[u]; 
	}
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n; 
	for(int i=1,x,y,a,b;i<n;i++) {
		cin >> x >> y >> a >> b; 
		graph[x].push_back({y, a, b}); 
		graph[y].push_back({x, a, b}); 
	}
	dfs(1, -1); 
	for(int i=1;i<n;i++) {
		int lca = qlca(i, i+1); 
		diff[i]++; diff[i+1]++; diff[lca]-=2; 
	}
	pd(1, -1); 
	for(int x=1;x<=n;x++) {
		for(auto&[y,a,b] : graph[x]) 
			ans += min((long long)(diff[(depth[x]<depth[y]?y:x)] * a), (long long)(b)); 
	}
	cout << ans/2 << '\n'; 
}
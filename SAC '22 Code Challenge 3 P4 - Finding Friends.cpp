#include <bits/stdc++.h>
using namespace std;
const int MM = 1e5+3; 
int n, q, dist[MM], up[MM][18], par[MM]; vector<int> graph[MM]; 
void dfs(int node, int par) {
	for(int u : graph[node]) {
		if(u == par) continue; 
		dist[u] = dist[node] + 1; 
		up[u][0] = node; 
		for(int i = 1; i < 18; i++) up[u][i] = up[up[u][i - 1]][i - 1]; 
		dfs(u, node); 
	}
}
int query_lca(int a, int b) {
	if(dist[a] < dist[b]) swap(a, b); 
	int k = dist[a] - dist[b]; 
	for(int j = 17; j >= 0; j--) {
		if(k >= (1 << j)) {
			a = up[a][j]; 
			k -= (1 << j); 
		}
	}
	if(a == b) return a; 
	for(int j = 17; j >= 0; j--) {
		if(up[a][j] != up[b][j]) 
			a = up[a][j], b = up[b][j]; 
	}
	return up[a][0]; 
}
int query_dist(int a, int b) {
	return dist[a] + dist[b] - 2 * dist[query_lca(a, b)]; 
}
struct Query {
	int type, u, v; 
}; 
int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
void merge(int x, int y) {
	int a = find(x), b = find(y); 
	if(a != b) par[b] = a; 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> q; 
	for(int i = 1; i <= n; i++) par[i] = i; 
 	for(int i = 1, x, y; i < n; i++) {
		cin >> x >> y; 
		graph[x].push_back(y); 
		graph[y].push_back(x); 
	}
	dfs(1, -1); 
	vector<Query> queries; 
	for(int i = 1, op, u, v; i <= q; i++) {
		cin >> op >> u >> v; 
		queries.push_back({op, u, v}); 
	}
	reverse(queries.begin(), queries.end()); 
	vector<int> answer; 
	for(auto& [op, u, v] : queries) {
		if(op == 2) merge(u, v); 
		else {
			if(find(u) != find(v)) answer.push_back(-1); 
			else answer.push_back(query_dist(u, v)); 
		}
	} 
	reverse(answer.begin(), answer.end()); 
	for(int x : answer) cout << x << '\n'; 
}
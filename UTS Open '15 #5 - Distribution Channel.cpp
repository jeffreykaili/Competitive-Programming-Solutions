#include <bits/stdc++.h>
using namespace std;
const int MM = 50003, LOG = 17; 
struct edge {int x, y, w, used;}; vector<edge> el; vector<pair<int, int>> graph[MM]; 
int n, m, up[MM][LOG], dep[MM], mx[MM][LOG], par[MM], MST, ans = INT_MAX, edges; 
int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
void merge(int x, int y) {
	int a = find(x), b = find(y); 
	if(a!=b) par[b]=a; 
}
void dfs(int node, int par) {
	for(auto [u, w] : graph[node]) {
		if(u == par) continue; 
		dep[u] = dep[node] + 1; up[u][0] = node; mx[u][0] = w; 
		for(int k=1; k<LOG; k++) {
			up[u][k] = up[up[u][k-1]][k-1]; 
			mx[u][k] = max(mx[u][k-1], mx[up[u][k-1]][k-1]); 
		}
		dfs(u, node); 
	}
}
int lca(int a, int b) {
	if(dep[a] < dep[b]) swap(a, b); 
	int k = dep[a] - dep[b]; 
	for(int j=LOG-1; j>=0; j--) 
		if(k >= (1<<j)) 
			a = up[a][j], k -= (1<<j);
	if(a==b) return a; 
	for(int j=LOG-1; j>=0; j--) 
		if(up[a][j] != up[b][j]) a = up[a][j], b = up[b][j]; 
	return up[a][0]; 
}
int q_max(int a, int b) {
	int t = lca(a, b), ak = dep[a] - dep[t], bk = dep[b] - dep[t], ret=0; 
	for(int j=LOG-1; j>=0; j--) {
		if(ak >= (1<<j)) ret = max(ret, mx[a][j]), ak -= (1<<j), a = up[a][j]; 
		if(bk >= (1<<j)) ret = max(ret, mx[b][j]), bk -= (1<<j), b = up[b][j]; 
	}
	return ret; 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> m; 
	for(int i=1;i<=n;i++) par[i]=i; 
	for(int i=1, x, y, w; i<=m; i++) {
		cin >> x >> y >> w; 
		el.push_back({x, y, w, 0}); 
	}
	sort(el.begin(), el.end(), [](edge a, edge b) { return a.w < b.w; }); 
	for(auto &e : el) {
		if(find(e.x) != find(e.y)) {
			merge(e.x, e.y); 
			graph[e.x].push_back({e.y, e.w}); graph[e.y].push_back({e.x, e.w}); 
			e.used = 1; MST += e.w; edges++; 
		}
	}
	if(edges != n-1) { cout << -1 << '\n'; return 0; }
	dfs(1, -1); 
	for(auto e : el) {
		if(e.used) continue; 
		int tmpMST = MST + e.w - q_max(e.x, e.y); 
		if(tmpMST > MST) ans = min(ans, tmpMST); 
	}
	cout << (ans == INT_MAX ? -1 : ans) << '\n'; 
}
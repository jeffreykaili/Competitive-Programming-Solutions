#include <bits/stdc++.h>
using namespace std;
const int MM = 2003; 
struct Edges {
	int x, y, w; 
	bool operator<(Edges other) const {
		return w > other.w; 
	}
}; vector<Edges> edges; 
struct Process {
	int i; pair<int, int> val; 
	bool operator<(Process other) const {
		return val.first > other.val.first; 
	}  
}; vector<Process> process; 
int n, ans, px[MM], py[MM], on_weight; pair<int, int> dp[MM];  
int dist(int x, int y) {
	int dx = (px[x] - px[y]), dy = (py[x] - py[y]); 
	return dx * dx + dy * dy; 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n; 
	for(int i = 1; i <= n; i++) {
		cin >> px[i] >> py[i]; 
		for(int j = 1; j < i; j++) 
			edges.push_back({i, j, dist(i, j)}); 
	} sort(edges.begin(), edges.end()); 
	for(int i = 1; i <= n; i++) dp[i] = {1, dist(i, 0)}; 
	on_weight = edges[0].w; 
	auto update = [&]() -> void {
		sort(process.begin(), process.end()); 
		for(auto& p : process) 
			if(dp[p.i].second != p.val.second) dp[p.i] = p.val; 
		process.clear(); 
	};
	for(auto& edge : edges) {
		auto& [x, y, w] = edge; 
		if(w != on_weight) update();
		on_weight = w; 
		if(dp[x].first + 1 > dp[y].first && dp[x].second > w) 
			process.push_back({y, {dp[x].first + 1, w}}); 
		if(dp[y].first + 1 > dp[x].first && dp[y].second > w) 
			process.push_back({x, {dp[y].first + 1, w}}); 
	} update();  
	for(int i = 1; i <= n; i++) ans = max(ans, dp[i].first);
	cout << ans << '\n';  
 }
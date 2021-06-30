#include <bits/stdc++.h>
using namespace std;
const int MM = 1004; 
struct {int x1, y1, x2, y2, t;} q[MM];  
int n, T, p, m; map<int, int> rnkx, rnky, revx, revy; long long diff[2*MM][2*MM], ans; 
void process(int& x1, int& y1, int& x2, int& y2) { x1=rnkx[x1], y1=rnky[y1], x2=rnkx[x2], y2=rnky[y2]; }
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> T; 
	for(int i=1; i<=n; i++) {
		cin >> q[i].x1 >> q[i].y1 >> q[i].x2 >> q[i].y2 >> q[i].t; 
		rnkx[q[i].x1]=0; rnky[q[i].y1]=0; rnkx[q[i].x2]=0; rnky[q[i].y2]=0; 
	}
	for(auto& [k, v] : rnkx) { v=++p; revx[v]=k; }
	for(auto& [k, v] : rnky) { v=++m; revy[v]=k; }
	for(int i=1; i<=n; i++) {
		auto [x1, y1, x2, y2, t] = q[i]; process(x1,y1,x2,y2); 
		diff[x1][y1] += t; diff[x2][y2] += t; 
		diff[x1][y2] -= t; diff[x2][y1] -= t; 
	}
	for(int x=1; x<=p; x++) {
		for(int y=1; y<=m; y++) {
			diff[x][y] += diff[x-1][y] + diff[x][y-1] - diff[x-1][y-1]; 
			if(diff[x][y] >= T) ans += 1LL * (revy[y+1] - revy[y]) * (revx[x+1] - revx[x]);  
		}
	}
	cout << ans << '\n'; 
}
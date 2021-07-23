#include <bits/stdc++.h>
using namespace std;
const int MM = 1e3+3; 
int k, rht[MM], lft[MM], m, n, pre[MM]; char x; 
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> k; 
	for(int t=1, ans; t<=k; t++) {
		cin >> m >> n; memset(pre, 0, sizeof(pre)); ans = 0; 
		for(int i=1; i<=m; i++) {
			for(int j=1; j<=n; j++) {
				cin >> x; pre[j] = (x == 'R' ? 0 : pre[j] + 1); 
			}
			stack<pair<int, int>> st; 
			for(int i=1; i<=n; i++) {
				while(st.size() && pre[i] < st.top().first) {
					rht[st.top().second] = i; st.pop(); 
				} 
				st.push({pre[i], i}); 
			} 
			while(st.size()) { rht[st.top().second] = n+1; st.pop(); }
			for(int i=n; i>=1; i--) {
				while(st.size() && pre[i] < st.top().first) {
					lft[st.top().second] = i; st.pop(); 
				} 
				st.push({pre[i], i}); 
			}
			while(st.size()) { lft[st.top().second] = 0; st.pop(); }
			for(int i=1; i<=n; i++) ans = max(ans, (rht[i] - lft[i] - 1) * pre[i] * 3); 
		}
		cout << ans << '\n'; 
	}
}
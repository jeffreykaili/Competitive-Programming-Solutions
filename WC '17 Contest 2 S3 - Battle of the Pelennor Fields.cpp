#include <bits/stdc++.h>
using namespace std;
const int MM = 1e6, MX = 3e5+3; 
struct query{int e, p, r;}; 
int n, p, ans[MX], t[MM], cnt; query ev[MX]; map<int, int> mp; vector<int> field[MM]; 
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n; 
	for(int i=1; i<=n; i++) {
		auto& x = ev[i]; 
		cin >> x.e >> x.p; mp[x.p]=0; 
		if(x.e == 2) {
			cin >> x.r; mp[x.p-x.r]=0; mp[x.p+x.r]=0; 
		} 
	}
	for(auto&[o,v] : mp) v=++p; 
	for(int i=1; i<=n; i++) {
		auto x = ev[i]; 
		if(x.e == 1) continue; 
		int lft = x.p - x.r, rht = x.p + x.r; 
		field[mp[lft]].push_back(i); field[mp[rht]+1].push_back(-i); 
	}
	set<int> res; 
	for(int i=1; i<=p; i++) {
		for(int x : field[i]) {
			if(x < 0) res.erase(-x);
			else res.insert(x);  
		}
		if(!res.size()) t[i] = -1; 
		else t[i] = *res.begin(); 
	}
	for(int i=1; i<=n; i++) {
		auto x = ev[i]; 
		if(x.e == 2) continue; 
		if(t[mp[x.p]] == -1) continue; 
		int vun = max(i, t[mp[x.p]]); 
		ans[vun]++; 
	}
	for(int i=1; i<=n; i++) {
		cnt = cnt + (ev[i].e == 1) - ans[i]; 
		cout << cnt << '\n'; 
	}
}
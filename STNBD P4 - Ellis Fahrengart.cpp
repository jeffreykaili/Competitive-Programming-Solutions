#include <bits/stdc++.h>
using namespace std;
const int MM = 1e5+3; 
long long n, q, inv, cur_r, cur_l = 1, block_sz, a[MM], bit[MM], ans[MM], id = 1; map<int, int> mp;  
struct Query {
	int l, r, idx; 
	bool operator<(Query other) const {
		if(l / block_sz != other.l / block_sz) 
			return l / block_sz < other.l / block_sz; 
		return l / block_sz % 2 ? r < other.r : r > other.r;

	}
}; vector<Query> queries; 
void update(int i, int add) {
	for(; i < id + 1; i += i & (-i)) bit[i] += add; 
}
int query(int i) {
	int res = 0; 
	for(; i; i -= i & (-i)) res += bit[i];
	return res; 
}
void addl(int x) { 
	inv += query(a[x] - 1); 
	update(a[x], 1); 
}
void addr(int x) {
	inv += (cur_r - cur_l) - query(a[x]); 
	update(a[x], 1);  
}
void removel(int x) {
	inv -= query(a[x] - 1);
	update(a[x], -1);  
}
void remover(int x) {
	inv -= (cur_r - cur_l + 1) - query(a[x]);
	update(a[x], -1); 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n; block_sz = sqrt(n); 
	for(int i = 1; i <= n; i++) {
		cin >> a[i]; mp[a[i]] = 0; 
	}
	for(auto& [k, v] : mp) v = ++id; // compress
	for(int i = 1; i <= n; i++) a[i] = mp[a[i]];
	cin >> q; 
	for(int i = 1, l, r; i <= q; i++) {
		cin >> l >> r; 
		queries.push_back({l, r, i}); 
	} sort(queries.begin(), queries.end()); 
	for(Query q : queries) {
		while(cur_l > q.l) addl(--cur_l); 
		while(cur_r < q.r) addr(++cur_r); 
		while(cur_l < q.l) { removel(cur_l); cur_l++; }  
		while(cur_r > q.r) { remover(cur_r); cur_r--; }
		ans[q.idx] = inv;  
	}
	for(int i = 1; i <= q; i++) cout << ans[i] << '\n'; 
}
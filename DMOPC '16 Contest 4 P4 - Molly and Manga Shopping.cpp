#include <bits/stdc++.h>
using namespace std;
const int MM = 1e5+3; 
int n, q, block_sz, arr[MM], ans[MM], f[MM], cnt; 
struct Query {
	int l, r, idx; 
	bool operator<(Query other) const {
		if(l / block_sz != other.l / block_sz) 
			return l / block_sz < other.l / block_sz; 
		return r < other.r; 
	}
}; 
void add(int x) {
	f[arr[x]]++; 
	if(f[arr[x]] % 2 == 0) cnt++; 
	else if(f[arr[x]] != 1) cnt--; 
}
void remove(int x) {
	f[arr[x]]--; 
	if(f[arr[x]] % 2 == 0){
		if(f[arr[x]] != 0) cnt++; 
	} else cnt--; 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n; block_sz = sqrt(n); 
	for(int i = 1; i <= n; i++) cin >> arr[i]; 	
	vector<Query> queries; 
	cin >> q; 
	for(int i = 1, l, r; i <= q; i++) {
		cin >> l >> r; 
		Query q = {l, r, i}; 
		queries.push_back(q); 
	}
	sort(queries.begin(), queries.end()); 
	int cur_l = 1, cur_r = 0; 
	for(Query q : queries) {
 		while(cur_l > q.l) add(--cur_l); 
		while(cur_r < q.r) add(++cur_r); 
		while(cur_l < q.l) remove(cur_l++);
		while(cur_r > q.r) remove(cur_r--);
		ans[q.idx] = cnt;  
	} 
	for(int i = 1; i <= q; i++) cout << ans[i] << '\n'; 
}
#include <bits/stdc++.h>
using namespace std;
const int MM = 1e6+3; 
struct {int l, r, bug; bool lz;} seg[4*MM]; 
int n, m, t; 
void pushup(int root) { seg[root].bug = seg[2*root].bug + seg[2*root+1].bug; }
void pushdown(int root) {
	int lc = 2*root, rc = 2*root+1; 
	seg[lc].bug = (seg[lc].r - seg[lc].l + 1) - seg[lc].bug; 
	seg[rc].bug = (seg[rc].r - seg[rc].l + 1) - seg[rc].bug; 
	seg[lc].lz = !seg[lc].lz; 
	seg[rc].lz = !seg[rc].lz; 
	seg[root].lz = 0; 
}
void build(int l, int r, int root) {
	seg[root].l = l; seg[root].r = r; 
	if(l == r) {
		seg[root].bug = 1; 
		return; 
	} int mid = (l + r) / 2; 
	build(l, mid, 2*root); build(mid+1, r, 2*root+1); 
	pushup(root); 
}
void update(int l, int r, int root) {
	if(seg[root].l == l && seg[root].r == r) {
		seg[root].bug = (seg[root].r - seg[root].l + 1) - seg[root].bug; 
		seg[root].lz = !seg[root].lz; 
		return; 
	} 
	if(seg[root].lz) pushdown(root);  
	int mid = (seg[root].l + seg[root].r) / 2; 
	if(r <= mid) {
		update(l, r, 2*root); 
	} else if(l > mid) {
		update(l, r, 2*root+1); 
	} else {
		update(l, mid, 2*root); 
		update(mid+1, r, 2*root+1); 
	} pushup(root); 
}
int query(int l, int r, int root) {
	if(seg[root].l == l && seg[root].r == r) return seg[root].bug; 
	if(seg[root].lz) pushdown(root); 
	int mid = (seg[root].l + seg[root].r) / 2; 
	if(r <= mid) return query(l, r, 2*root); 
	else if(l > mid) return query(l, r, 2*root+1); 
	else return query(l, mid, 2*root) + query(mid+1, r, 2*root+1); 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> m >> t; 
	build(1, n, 1); 
	for(int i=1, a, b; i<=m; i++) {
		cin >> a >> b; 
		update(a, b, 1); 
		int l = 1, r = n, ans = -1; 
		while(l <= r) {
			int mid = (l + r) / 2; 
			if(query(1, mid, 1) >= t) {
				ans = mid; 
				r = mid - 1; 
			} else l = mid + 1; 
		}
		if(ans == -1) cout << "AC?" << '\n'; 
		else cout << ans << '\n'; 
	}
}
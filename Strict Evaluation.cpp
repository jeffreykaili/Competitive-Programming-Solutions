#include <bits/stdc++.h>
using namespace std;
const int MM = 1e5+3; 
struct {long long l, r, minv, lzadd, lzset;} seg[4*MM]; 
int n, q;
void pushup(int root) { seg[root].minv = min(seg[2*root].minv, seg[2*root+1].minv); } 
void pushdown(int root) {
	int lc = 2*root, rc = 2*root+1; 
	if(seg[root].lzadd != 0) {
		if(seg[lc].lzset == 0) seg[lc].lzadd += seg[root].lzadd; 
		else {
			seg[lc].lzset += seg[root].lzadd; 
			seg[lc].lzadd = 0; 
		} 
		if(seg[rc].lzset == 0) seg[rc].lzadd += seg[root].lzadd; 
		else {
			seg[rc].lzset += seg[root].lzadd; 
			seg[rc].lzadd = 0; 
		} // apply changes 
		seg[lc].minv += seg[root].lzadd; 
		seg[rc].minv += seg[root].lzadd; 
		seg[root].lzadd = 0; 
	} else if (seg[root].lzset != 0) {
		seg[lc].lzset = seg[rc].lzset = seg[root].lzset;
		seg[lc].lzadd = seg[rc].lzadd = 0;  
		seg[lc].minv = seg[rc].minv = seg[root].lzset; 
		seg[root].lzset = 0; 
	}
}
void build(int l, int r, int root) {
	seg[root].l = l; seg[root].r = r; 
	if(l == r) {
		cin >> seg[root].minv; 
		return; 
	}
	int mid = (l + r) / 2; 
	build(l, mid, 2*root); build(mid+1, r, 2*root+1); 
	pushup(root); 
}
void add(int l, int r, int root, int v) {
	if(seg[root].l == l && seg[root].r == r) {
		seg[root].minv += v; 
		if(seg[root].lzset == 0) seg[root].lzadd += v; 
		else seg[root].lzset += v; 
		return; 
	} pushdown(root); 
	int mid = (seg[root].l + seg[root].r) / 2;
	if(r <= mid) {
		add(l, r, 2*root, v); 
	} else if (l > mid) {
		add(l, r, 2*root+1, v); 
	} else {
		add(l, mid, 2*root, v); 
		add(mid+1, r, 2*root+1, v); 
	} pushup(root); 
}
void change(int l, int r, int root, int v) {
	if(seg[root].l == l && seg[root].r == r) {
		seg[root].minv = v; 
		seg[root].lzadd = 0; 
		seg[root].lzset = v; 
		return;  
	} pushdown(root); 
	int mid = (seg[root].l + seg[root].r) / 2; 
	if(r <= mid) {
		change(l, r, 2*root, v); 
	} else if(l > mid) {
		change(l, r, 2*root+1, v); 
	} else {	
		change(l, mid, 2*root, v); 
		change(mid+1, r, 2*root+1, v); 
	} pushup(root); 
}
long long query(int l, int r, int root) {
	if(seg[root].l == l && seg[root].r == r) return seg[root].minv; 
	pushdown(root); 
	int mid = (seg[root].l + seg[root].r) / 2; 
	if(r <= mid) return query(l, r, 2*root);
	else if(l > mid) return query(l, r, 2*root+1); 
	else return min(query(l, mid, 2*root), query(mid+1, r, 2*root+1)); 
}
int main() {	
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> q; 
	build(1, n, 1); 
	for(int i=1, op, l, r, v; i<=q; i++) {
		cin >> op >> l >> r; 
		if(op == 1) {
			cin >> v; add(l, r, 1, v); 
		} else if (op == 2) {
			cin >> v; change(l, r, 1, v); 
		} else cout << query(l, r, 1) << '\n'; 
	}
}
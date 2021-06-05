#include <bits/stdc++.h>
using namespace std;
// seg tree w/ lazy update, but with frequency array? 
const int MM = 250003; 
struct {int l, r, freq[10], lazy;} seg[4*MM]; 
int n, m, arr[MM]; string s; 
void pushup(int root) {
	for(int i=0;i<=9;i++) 
		seg[root].freq[i] = seg[2*root].freq[i] + seg[2*root+1].freq[i]; 
}
void pushdown(int root) {
	int lc = 2*root, rc = 2*root+1; 
	seg[lc].lazy += seg[root].lazy; seg[rc].lazy += seg[root].lazy; 
	map<int, int> mp; vector<int> tmplc(10), tmprc(10); 
	for(int i=0;i<=9;i++) mp[i] = (i+seg[root].lazy)%10; 
	for(auto&[k, v]:mp)  {
		tmplc[v] = seg[lc].freq[k]; 
		tmprc[v] = seg[rc].freq[k];  
	}
	for(int i=0;i<=9;i++) {
		seg[lc].freq[i] = tmplc[i]; 
		seg[rc].freq[i] = tmprc[i]; 
	}
	seg[root].lazy = 0; 
}
void build(int l, int r, int root) {
	seg[root].l = l; seg[root].r = r; 
	if(l==r) {
		seg[root].freq[arr[l]]++; 
		return; 
	}
	int mid = (l+r)/2; 
	build(l, mid, 2*root); build(mid+1, r, 2*root+1); 
	pushup(root); 
}
long long query(int l, int r, int root) {
	if(seg[root].l == l && seg[root].r == r) {
		long long res = 0; 
		for(int i=1;i<=9;i++) 
			res += 1LL * seg[root].freq[i] * i; 
		seg[root].lazy++; 
		int tmp = seg[root].freq[9]; 
		for(int i=9; i>=1; i--) seg[root].freq[i] = seg[root].freq[i-1]; 
		seg[root].freq[0] = tmp; 
		return res; 
	}
	if(seg[root].lazy) pushdown(root); 
	long long res; 
	int mid = (seg[root].l + seg[root].r) / 2; 
	if(r <= mid) res = query(l, r, 2*root); 
	else if (l > mid) res = query(l, r, 2*root+1); 
	else res = query(l, mid, 2*root) + query(mid+1, r, 2*root+1); 
	pushup(root); 
	return res; 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin>>n>>m>>s; 
	for(int i=1;i<=n;i++) arr[i] = s[i-1] - '0'; 
	build(1, n, 1); 
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y; 
		cout << query(x, y, 1) << '\n'; 
	}
}
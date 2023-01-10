#include <bits/stdc++.h>
using namespace std;
const int MM = 2e5+3; 
int n, q, block_sz, arr[MM], blocks[450][MM]; 
void fac(int idx, int add) {
	for(int k = 1; k * k <= arr[idx]; k++) {
		if(arr[idx] % k == 0) {
			blocks[(idx - 1) / block_sz + 1][k] += add; 
			if(k * k != arr[idx]) blocks[(idx - 1) / block_sz + 1][arr[idx] / k] += add; 
		}
	}
}
int query(int idx, int x) {
	int res = 0; 
	for(int i = 1; i <= (idx - 1) / block_sz; i++) res += blocks[i][x]; 
	for(int i = max(1, (idx - 1) / block_sz * block_sz + 1); i <= idx; i++) res += arr[i] % x == 0; 
	return res; 
}
void update(int idx, int x) {
	fac(idx, -1); 
	arr[idx] = x; 
	fac(idx, 1); 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> q; 
	block_sz = sqrt(n); 
	for(int i = 1; i <= n; i++) {
		cin >> arr[i]; fac(i, 1); 
	}
	for(int i = 1, op, l, r, x, u, v; i <= q; i++) {
		cin >> op; 
		if(op == 1) {
			cin >> l >> r >> x; 
			cout << query(r, x) - query(l - 1, x) << '\n'; 
		} else {
			cin >> u >> v; 
			update(u, v); 
		}
	}
}
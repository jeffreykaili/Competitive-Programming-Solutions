#include <bits/stdc++.h>
using namespace std;
const int MM = 53, mod = 1e9+7; 
#define ll long long 
ll n, k, res; vector<vector<ll>> adj(MM, vector<ll>(MM, 0)), tmp; 
vector<vector<ll>> mul(vector<vector<ll>> a, vector<vector<ll>> b) {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			tmp[i][j] = 0; 
			for(int k=1; k<=n; k++) 
				tmp[i][j] = (tmp[i][j] + (a[i][k] * b[k][j])%mod)%mod; 
		}
	} return tmp; 
}
vector<vector<ll>> matrix_mul(vector<vector<ll>> a, ll exp) {
	if(exp == 1) return a; 
	vector<vector<ll>> tmp = matrix_mul(a, exp / 2); 
	tmp = mul(tmp, tmp); 
	if(exp & 1) return mul(a, tmp); 
	return tmp; 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> k; tmp = adj; 
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) cin >> adj[i][j]; 
	vector<vector<ll>> ans = matrix_mul(adj, k); 
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) res = (res + ans[i][j]) % mod; 
	cout << res << '\n'; 
}
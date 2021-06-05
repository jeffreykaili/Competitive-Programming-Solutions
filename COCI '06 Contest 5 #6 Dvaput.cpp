#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
const int MM = 2e5+3, base = 131, mod1 = 1e9+7, mod2 = 1e9+9, RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { int operator()(pair<long long, long long> x) const { return x.first* 31 + x.second; }};
long long n, hsh1[MM], hsh2[MM], pows1[MM], pows2[MM]; string s; gp_hash_table<pair<int, int>, null_type, chash> vis;
int get_hsh(int l, int r, long long hsh[], long long pows[], int mod) {return ((hsh[r] - hsh[l-1] * pows[r-l+1])%mod+mod)%mod;}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> s; 
	pows1[0] = pows2[0] = 1; 
	for(int i=1;i<=n;i++) {
		int p = s[i-1] - 'a' + 1; 
		hsh1[i] = (hsh1[i-1] * base + p)%mod1; 
		pows1[i] = (pows1[i-1] * base)%mod1; 
		hsh2[i] = (hsh2[i-1] * base + p)%mod2; 
		pows2[i] = (pows2[i-1] * base)%mod2; 
	}
	auto ok = [&](int L) -> bool {
		vis.clear();
		for(int i=1; i<=n; i++) {
			if(i+L-1>n) break; 
			pair<int, int> hash = {get_hsh(i, i+L-1, hsh1, pows1, mod1), get_hsh(i, i+L-1, hsh2, pows2, mod2)}; 
			if(vis.find(hash) != vis.end()) return true; 
			vis.insert(hash); 
		}
		return false; 
	}; 
	int l = 1, r = n, mid, ans = 0; 
	while(l<=r) {
		mid = (l+r)/2; 	
		if(ok(mid)) ans = mid, l = mid + 1; 
		else r = mid - 1; 		
	}
	cout << ans << '\n'; 
}
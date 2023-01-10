#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
const int MM = 5003, seed = 131, mod1 = 1e9+7, mod2 = 1e9+9; 
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
long long n, hsh1[MM], pows1[MM], hsh2[MM], pows2[MM]; gp_hash_table<long long, null_type> str;
long long get_hash(int l, int r, long long hsh[], long long pows[], int mod) {
	return (1LL * (hsh[r] - hsh[l-1] * pows[r-l+1]) % mod + mod) % mod; 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n; pows1[0] = pows2[0] = 1; 
	for(int t=1; t<=n; t++) {
		string s; cin >> s; 
		for(int i=1; i<=int(s.size()); i++) {
			int p = s[i-1] - 'a' + 1; 
			hsh1[i] = (hsh1[i-1] * seed + p) % mod1; 
			pows1[i] = (pows1[i-1] * seed) % mod1; 
			hsh2[i] = (hsh2[i-1] * seed + p) % mod2; 
			pows2[i] = (pows2[i-1] * seed) % mod2; 
		} int ans = 0; bool done = 0; 
		for(int L = 1; L <= int(s.size()); L++) {
			if(done) { ans += s.size() - L + 1; continue; }
			for(int i=1; i + L - 1 <= int(s.size()); i++) 
				str.insert((get_hash(i, i + L - 1, hsh1, pows1, mod1) << 31) | get_hash(i, i + L - 1, hsh2, pows2, mod2)); 
			if(str.size() == s.size() - L + 1) done = 1; 
			ans += str.size(); str.clear(); 
		} cout << ans + 1 << '\n'; 
	}
}
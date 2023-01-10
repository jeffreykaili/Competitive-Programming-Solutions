#include <bits/stdc++.h>
using namespace std;
const int MM = 3e5+3; 
#define m first
#define v second
long long n, k, ans; pair<int, int> jwl[MM]; 
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> k; multiset<int> ms;
	for(int i=1; i<=n; i++) cin >> jwl[i].m >> jwl[i].v; 
	sort(jwl + 1, jwl + n + 1, [](pair<int, int> a, pair<int, int> b) { return a.v != b.v ? a.v > b.v : a.m > b.m; }); 
	for(int i=1, x; i<=k; i++) { cin >> x; ms.insert(x); }
	for(int i=1; i<=n; i++) {
		auto& [mi, vi] = jwl[i]; 
		auto it = ms.lower_bound(mi);
		if(it == ms.end()) continue; 
		ans += vi; ms.erase(it); 
	} cout << ans << '\n'; 
}
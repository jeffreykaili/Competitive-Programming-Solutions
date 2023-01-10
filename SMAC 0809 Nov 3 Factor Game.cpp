#include <bits/stdc++.h>
using namespace std;
int n, moves; map<int, int> mp; 
int calc(int x) { 
	if(mp[x]) return mp[x]; 
	if(x <= 3) return mp[x] = 2; 
	int ans = 1;
	for(int i=2; i*i<=x; i++) 
		if(x % i == 0) 
			ans = max(ans, min(calc(x / i), calc(i)) + 1); 
	return mp[x] = ans; 
}
int main() {
	while(true) {
		cin >> n; mp[1] = 1; 
		if(n == 1) break; 
		pair<int, int> best = {1, n}; 
		moves = 1; 
		for(int i=1; i*i<=n; i++) {
			if(n % i == 0) {
				int res = min(calc(i), calc(n/i)); 
				if(res >= moves) {
					best = {i, n/i}; 
					moves = res; 
				}
			}
		} cout << best.first << " " << best.second << endl; 
	}	
}
#include <bits/stdc++.h>
using namespace std;
const int MM = 5e5+3; 
int n, i; char op; long long w, width[MM], cute[MM], bst[MM]; 
map<long long, int, greater<long long>> scores; 	
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> n >> w; 
	for(int q=1,p,c;q<=n;q++) {
		cin >> op; 
		if(op == 'A') {
			cin >> p >> c; i++;
			width[i] = width[i-1] + p; 
			cute[i] = cute[i-1] + c;  
			auto bs = [&](int l, int r, long long need) -> int {
				int ans = 0; 
				while(l<=r) {
					int mid = (l+r)/2; 
					if(width[mid] >= need) r = mid - 1, ans = mid; 
					else l = mid + 1; 
				}
				return ans; 
			}; 
			int index = bs(0, i, width[i]-w); 
			scores[cute[i]-cute[index]]++; 
			bst[i] = cute[i]-cute[index]; 
			for(auto it = scores.begin(); it != scores.end(); it++) {
				long long sc = it->first, freq = it->second; 
				if(freq) { cout << sc << '\n'; break;}
			}
		} else scores[bst[i--]]--; 
	}
}
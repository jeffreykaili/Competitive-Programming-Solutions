#include <bits/stdc++.h>
using namespace std;
const int MM = 2003;  
int h, k, pos[MM]; 
bool works(int L) {
	for(int i = 1; i <= h; i++) {
		int left = pos[i], right = (pos[i] + 2 * L), cnt = 1; 
		for(int j = i + 1; j < i + h; j++) {
			if(right >= 1e6) {
				if(pos[j] >= left || pos[j] <= right - 1e6) continue; 
				else cnt++, left = pos[j], right = pos[j] + 2 * L; 
			} 
			else if(left > pos[j] || right < pos[j]) 
				cnt++, left = pos[j], right = pos[j] + 2 * L; 
		} if(cnt <= k) return true; 
	} return false; 
}
int main() {
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> h; 
	for(int i = 1; i <= h; i++) cin >> pos[i];
	sort(pos + 1, pos + h + 1); 
	for(int i = 1; i <= h; i++) pos[i + h] = pos[i];  
	cin >> k; 
	int l = 0, r = 1e6, ans = 0;
	while(l <= r) {
		int mid = (l + r) / 2; 
		if(works(mid)) ans = mid, r = mid - 1; 
		else l = mid + 1; 
	} cout << ans << '\n'; 
}
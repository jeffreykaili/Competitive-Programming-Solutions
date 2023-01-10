#include <bits/stdc++.h>
using namespace std;
const int MM = 1003; 
int r, s, lft[MM], rht[MM], a[MM][MM], psa[MM], ans;
void calc() {
	stack<pair<int,int>> st; 
	for(int i=1; i<s; i++) {
		while(st.size() && psa[i] < st.top().first) {
			rht[st.top().second] = i; st.pop(); 
		} st.push({psa[i], i}); 
	} while(st.size()) { rht[st.top().second] = s; st.pop(); }
	for(int i=s-1; i>=1; i--) {
		while(st.size() && psa[i] < st.top().first) {
			lft[st.top().second] = i; st.pop(); 
		} st.push({psa[i], i}); 
	} while(st.size()) { lft[st.top().second] = 0; st.pop(); }
	for(int i=1; i<s; i++) ans = max(ans, (rht[i] - lft[i]) * (psa[i]+1)); 
} 
int main() {	
	cin.tie(0); cout.tie(0); cin.sync_with_stdio(0); 
	cin >> r >> s; 
	for(int i=1; i<=r; i++) 
		for(int j=1; j<=s; j++) 
			cin >> a[i][j]; 
	for(int i=1; i<r; i++) {
		for(int j=1; j<s; j++)
			psa[j] = (a[i][j] + a[i+1][j+1] <= a[i+1][j] + a[i][j+1] ? psa[j] + 1 : 0); 
		calc();  
	}
	cout << ans << '\n'; 
}
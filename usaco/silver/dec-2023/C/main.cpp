#include <bits/stdc++.h>
using namespace std;

#define vt vector

int dx[4]={-2, -1, 1, 2};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t, c, x; cin>>t>>c;
	vt<bool> targets(2e5+5, 0);
	for (int i=0; i<t; i++) {
		cin>>x;
		targets[x+1e5+2]=1;
	}
	string s; cin>>s;
	vt<int> loc(c); int idx=1e5+2;
	vt<vt<int>> freq(4, vt<int>(2e5+5, 0));
	vt<int> cnt(4, 0);
	for (int i=0; i<c; i++) {
		idx+=s[i]=='R';
		idx-=s[i]=='L';
		loc[i]=idx;
		if (s[i]=='F') {
			for (int j=0; j<4; j++) if (!freq[j][idx] && targets[idx]) cnt[j]++;
			for (int j=0; j<4; j++) freq[j][idx]++;
		}
	}
	int ans=cnt[0]+(!freq[0][loc[c-1]] && targets[loc[c-1]-(s[c-1]=='R')+(s[c-1]=='L')]);
	for (int i=c-1; i>0; i--) {
		if (s[i]=='F') {
			for (int j=0; j<4; j++) if (--freq[j][loc[i]]==0 && targets[loc[i]]) cnt[j]--;
			for (int j=0; j<4; j++) {
				if (!freq[j][loc[i]+dx[j]] && targets[loc[i]+dx[j]]) cnt[j]++;
				freq[j][loc[i]+dx[j]]++;
			}
		}
		if (s[i-1]=='F') {
			ans=max(ans, max(cnt[1]-(freq[1][loc[i-1]]==1 && targets[loc[i-1]]), cnt[2]-(freq[2][loc[i-1]]==1 && targets[loc[i-1]])));
		} else if (s[i-1]=='R') {
			ans=max(ans, max(cnt[0], cnt[1]+(!freq[1][loc[i-1]-1] && targets[loc[i-1]-1])));			
		} else if (s[i-1]=='L') {
			ans=max(ans, max(cnt[3], cnt[2]+(!freq[2][loc[i-1]+1] && targets[loc[i-1]+1])));
		}
	}
	cout << ans << endl;
}

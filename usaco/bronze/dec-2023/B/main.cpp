#include <bits/stdc++.h>

using namespace std;

#define vt vector
#define pb push_back

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; cin>>n;
	string s; cin>>s;
	int l=0, r=n-1, ni=INT_MAX;
	vt<int> d;
	while (l<n && s[l]=='1') l++;
	if (l>0) {
		ni=min(ni, l-1);
		d.pb(l);
	}
	if (l<n) {
		while (r>=0 && s[r]=='1') r--;
		if (r<n-1) {
			ni=min(ni, n-r-2);
			d.pb(n-r-1);
		}
	}
	while (l<=r) {
		int cnt=0;
		if (s[l]=='0') {
			l++;
			continue;
		}
		while (l<=r && s[l]=='1') l++, cnt++;
		d.pb(cnt);	
		ni=min(ni, (cnt-1)/2);
	}
	int ans=0;
	for (auto& x : d) ans+=x/(ni*2+1)+(x%(ni*2+1)>0);
	cout<<ans;
}
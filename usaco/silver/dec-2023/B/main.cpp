#include <bits/stdc++.h>
using namespace std;

#define vt vector

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, k, x; cin>>n>>k;
	vt<int> v1(n, -1), v2(n, -1);
	for (int i=0; i<k; i++) {
		cin>>x; --x;
		v1[x]=i;
	}
	for (int i=0; i<k; i++) {
		cin>>x; --x;
		v2[x]=i;
	}
	int ans=0;
	for (int i=0; i<n; i++) ans+=v1[i]==-1 && v2[i]==-1;
	vt<int> c1(k, 0), c2(k, 0);
	for (int i=0; i<n; i++) {
		if (v1[i]!=-1 && v2[i]!=-1) {
			c1[(v1[i]-v2[i]+k)%k]++;
			c2[(v1[i]+v2[i])%k]++;
		}
	}
	int ma=0;
	for (int i=0; i<k; i++) ma=max(ma, max(c1[i], c2[i]));
	cout << ans+ma << endl;
}

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define f first
#define s second

#define vt vector
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

vt<ll> ld(1e6+1), rd(1e6+1);

ll ts(ll a, ll b) {
	int l=0, r=1e6;
	auto cost=[&](int y) { return ld[y]*a+rd[y]*b; };
	while (r-l>30) {
		int m1 = l+(r-l)/3;
		int m2 = r-(r-l)/3;
		if (cost(m1)>cost(m2)) l=m1;
		else r=m2;
	}
	ll mi=LLONG_MAX;
	int idx;
	for (int i=l; i<=r; i++) if (cost(i)<mi) idx=i, mi=cost(i);
	return cost(idx);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, q, x, a, b, cnt; cin>>n;
	ll dist;
	vt<int> v(1e6+1, 0);
	for (int i=0; i<n; i++) {
		cin>>x;
		v[x]++;
	}
	cnt=0, dist=0;
	for (int i=0; i<=1e6; i++) {
		dist+=cnt;
		ld[i]=dist;
		cnt+=v[i];
	}
	cnt=0, dist=0;
	for (int i=1e6; i>=0; i--) {
		dist+=cnt;
		rd[i]=dist;
		cnt+=v[i];
	}
	cin>>q;
	for (int i=0; i<q; i++) {
		cin>>a>>b;
		cout << ts(a, b) << endl;
	}
}

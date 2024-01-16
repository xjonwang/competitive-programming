#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define f first
#define s second

#define vt vector
#define pb push_back
#define all(x) (x).begin(), (x).end()

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m; cin>>n>>m;
	vt<ll> v(n);
	for (int i=0; i<n; i++) cin>>v[i];
	ll c;
	for (int i=0; i<m; i++) {
		cin>>c;
		ll h=0;
		for (int j=0; j<n; j++) {
			ll t=v[j];
			v[j]+=max(min(c, v[j])-h, 0ll);
			h=max(h, t);
			if (t>=c) break;
		}
	}
	for (auto& x : v) cout << x << endl;
}
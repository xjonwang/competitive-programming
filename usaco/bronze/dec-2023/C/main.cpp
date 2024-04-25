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

int n;
bool p;

bool check(ll x, vt<int>& a, vt<int>& h, vt<pii>& v) {
	vt<pll> t(n);
	for (int i=0; i<n; i++) t[i].f=h[i]+x*a[i], t[i].s=i;
	sort(all(t), [](const pll& a, const pll& b) { return a.f!=b.f ? a.f>b.f : a.s<b.s; });
	for (int i=0; i<n; i++) {
		if (t[i].s!=v[i].s) {
			return a[t[i].s]>=a[v[i].s];
		} else if (i>0 && v[i-1].f<v[i].f && t[i].f==t[i-1].f) {
			return a[t[i-1].s]>a[t[i].s] ? false : true;
		} else if (i>0 && v[i-1].f==v[i].f && t[i-1].f>t[i].f) {
			return a[t[i-1].s]>=a[t[i].s] ? true : false;
		}
	}
	p=1;
	return true;
}

void solve() {
	cin>>n;
	vt<int> h(n), a(n);
	for (int i=0; i<n; i++) cin>>h[i];
	for (int i=0; i<n; i++) cin>>a[i];
	vt<pii> v(n);	
	for (int i=0; i<n; i++) cin>>v[i].f, v[i].s=i;
	sort(all(v));
	for (int i=0; i<n; i++) {
		if (v[i].f>i) {
			cout << -1 << endl;
			return;
		}
	}
	ll l=-1, r=1e9;
	p=0;
	for (ll i=r-l; i>0; i/=2) while (l+i<=r && !check(l+i, a, h, v)) l+=i;
	if (p) cout << l+1 << endl;
	else cout << -1 << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; cin>>t;
	for (int i=0; i<t; i++) solve();
}
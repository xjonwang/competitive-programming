#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define ar array

#define vt vector
#define pb push_back
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define pll pair<ll, ll>
#define pii pair<int, int>
#define f first
#define s second

#define F_OR(i, a, b, s) for (int i=(a); (s)>0?i<(b):i>(b); i+=(s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)
#define EACH(x, a) for (auto& x: a)

#define MX 10000000

bool g[MX];
int d[MX];
vt<pair<ll, int>> sq;

void init() {
	fill(g, g+MX, 1);
	FOR(i, 2, MX) {
		if (d[i]) continue;
		d[i]=1;
		for (int j=2; i*j<MX; j++) {
			d[i*j]++;
			if (j%i==0) g[i*j]=0;
		}
	}
	FOR(i, 2, MX) if (g[i]) sq.pb({i, d[i]});
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	init();
	int t; cin>>t;
	ll n;
	FOR(t) {
		cin>>n;
		ll ans=0;
		for (auto &[x, y] : sq) {
			if (x*x>n) break;
			if (y&1) ans+=n/(x*x);
			else ans-=n/(x*x);
		}
		cout<< n-ans << endl;
	}
}
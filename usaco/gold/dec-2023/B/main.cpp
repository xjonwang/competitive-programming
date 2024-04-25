#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>

#define vt vector
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

struct node {
	int l, p;
	ll s;
};

struct trav {
	int v, l, o;
	trav(int _v, int _l, int _o) : v(_v), l(_l), o(_o) {}; 
};

struct cmp {
	bool operator()(const trav& a, const trav& b) { return a.l!=b.l ? a.l>b.l : a.o<b.o; };
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, a, b, c; cin>>n>>m;
	vt<vt<pii>> radj(n);
	vt<int> out(n, 0);
	for (int i=0; i<m; i++) {
		cin>>a>>b>>c; --a, --b;
		radj[b].pb({a, c});
		out[a]++;
	}
	priority_queue<trav, vt<trav>, cmp> q;
	vt<node> dp(n, {0, 0, 0});
	for (int i=0; i<n; i++) if (out[i]==0) q.push({i, 0, 0});
	while (sz(q)) {
		auto [v, l, o]=q.top(); q.pop();
		for (auto& [u, c] : radj[v]) {
			if (dp[v].l+1>dp[u].l) dp[u]={dp[v].l+1, c, dp[v].s+c};
			else if (dp[v].l+1==dp[u].l && c<dp[u].p) dp[u]={dp[v].l+1, c, dp[v].s+c};
			if (--out[u]==0) q.push(trav(u, dp[u].p, dp[u].l));
		}
	}
	for (int i=0; i<n; i++) cout << dp[i].l << " " << dp[i].s << endl;
}
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define ar array

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

template<class T> bool umin(T& a, const T& b) {
	return b<a?a=b, 1:0;
}
template<class T> bool umax(T& a, const T& b) { 
	return a<b?a=b, 1:0;
} 

ll FIRSTTRUE(function<bool(ll)> f, ll lb, ll rb) {
	while(lb<rb) {
		ll mb=(lb+rb)/2;
		f(mb)?rb=mb:lb=mb+1; 
	} 
	return lb;
}
ll LASTTRUE(function<bool(ll)> f, ll lb, ll rb) {
	while(lb<rb) {
		ll mb=(lb+rb+1)/2;
		f(mb)?lb=mb:rb=mb-1; 
	} 
	return lb;
}

template<class A> void read(vt<A>& v);
template<class A, size_t S> void read(ar<A, S>& a);
template<class A, class B> void read(pair<A, B>& x);
template<class T> void read(T& x) {
	cin >> x;
}
void read(double& d) {
	string t;
	read(t);
	d=stod(t);
}
void read(long double& d) {
	string t;
	read(t);
	d=stold(t);
}
template<class H, class... T> void read(H& h, T&... t) {
	read(h);
	read(t...);
}
template<class A> void read(vt<A>& x) {
	EACH(a, x)
		read(a);
}
template<class A, size_t S> void read(array<A, S>& x) {
	EACH(a, x)
		read(a);
}
template<class A, class B> void read(pair<A, B>& x) {
	cin >> x.first >> x.second;
}


string to_string(char c) {
	return string(1, c);
}
string to_string(bool b) {
	return b?"true":"false";
}
string to_string(const char* s) {
	return string(s);
}
string to_string(string s) {
	return s;
}
string to_string(vt<bool> v) {
	string res;
	FOR(sz(v))
		res+=char('0'+v[i]);
	return res;
}

template<size_t S> string to_string(bitset<S> b) {
	string res;
	FOR(S)
		res+=char('0'+b[i]);
	return res;
}
template<class T> string to_string(T v) {
    bool f=1;
    string res;
    EACH(x, v) {
		if(!f)
			res+=' ';
		f=0;
		res+=to_string(x);
	}
    return res;
}
template<class A, class B> string to_string(pair<A, B>& x) {
	return to_string(x.first) + ' ' + to_string(x.second);
}

template<class A> void write(A x) {
	cout << to_string(x);
}
template<class H, class... T> void write(const H& h, const T&... t) { 
	write(h);
	write(t...);
}
void print() {
	write("\n");
}
template<class H, class... T> void print(const H& h, const T&... t) { 
	write(h);
	if(sizeof...(t))
		write(' ');
	print(t...);
}

#define LI make_pair(0ll, (ll)1e18)
#define RI make_pair((ll)1e18, 0ll)

vt<ll> w;
vt<vt<pair<int, ll>>> adj1, adj2;
vt<int> par, d;
vt<ll> d1, d2, pe1, pe2, sub, dp;
vt<vt<int>> up;
vt<vt<pll>> trav1, trav2;

void dfs(vt<vt<pair<int, ll>>> &adj, vt<ll> &wdepth, vt<ll> &pe, int v, ll wd, int p=-1) {
	d[v]=p!=-1 ? d[p]+1 : 0;
	wdepth[v]=wd;
	for (auto &[u, w] : adj[v]) {
		if (u!=p) {
			adj[u].erase(find(all(adj[u]), make_pair(v, w)));
			up[u][0]=v;
			par[u]=v;
			pe[u]=w;
			dfs(adj, wdepth, pe, u, wd+w, v);
		}
	}
}

void dfs1(int v, int p=-1) {
	sub[v]=d1[v]+d2[v]+w[v];
	for (auto &[u, _] : adj1[v]) {
		dfs1(u, v);
		umin(sub[v], sub[u]);
	}
}

void dfs2(int v, int p=-1) {
	vt<ll> l(sz(adj1[v])+1, 1e18), r(sz(adj1[v])+1, 1e18);
	FOR(sz(adj1[v])) l[i+1]=min(l[i], sub[adj1[v][i].f]);
	FOR(i, sz(adj1[v])-1, -1, -1) r[i]=min(r[i+1], sub[adj1[v][i].f]);
	FOR(sz(adj1[v])) {
		int u=adj1[v][i].f;
		dp[u]=min(w[v]-d1[v]-d2[v], min(dp[v], min(l[i], r[i+1])-2*d1[v]-2*d2[v]));
		dfs2(u, v);
	}
}

pll merge(pll st, pll l, pll r) {
	return {min(st.f+l.f, st.s+r.f), min(st.f+l.s, st.s+r.s)};
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, x, y; read(n);
	w.resize(n); read(w);
	adj1.resize(n), adj2.resize(n), par.resize(n), d.resize(n), d1.resize(n), d2.resize(n), pe1.resize(n), pe2.resize(n);
	sub.resize(n), dp.resize(n); dp[0]=1e18;
	up.assign(n, vt<int>(19, -1));
	trav1.assign(n, vt<pll>(19, {1e18, 1e18})), trav2.assign(n, vt<pll>(19, {1e18, 1e18}));
	ll a, b;
	FOR(n-1) {
		read(x, y, a, b); --x, --y;
		adj1[x].pb({y, a}), adj1[y].pb({x, a});
		adj2[x].pb({y, b}), adj2[y].pb({x, b});
	}
	dfs(adj1, d1, pe1, 0, 0);
	dfs(adj2, d2, pe2, 0, 0);
	dfs1(0);
	dfs2(0);
	FOR(n) w[i]=min(sub[i]-d1[i]-d2[i], d1[i]+d2[i]+dp[i]);
	FOR(i, 1, n) {
		trav1[i][0].f=min(pe1[i], w[i]+pe2[i]+w[par[i]]);
		trav1[i][0].s=min(pe1[i]+w[par[i]], w[i]+pe2[i]);
		trav2[i][0].f=min(pe2[i]+w[par[i]], w[i]+pe1[i]);
		trav2[i][0].s=min(pe2[i], w[i]+pe1[i]+w[par[i]]);
	}
	FOR(i, 1, 19) {
		FOR(j, n) {
			if (up[j][i-1]!=-1) {
				int t=up[j][i-1];
				up[j][i]=up[t][i-1];
				trav1[j][i]=merge(trav1[j][i-1], trav1[t][i-1], trav2[t][i-1]);
				trav2[j][i]=merge(trav2[j][i-1], trav1[t][i-1], trav2[t][i-1]);
			}
		}
	}
	auto lift=[&](int x, int k) {
		FOR(19) if (k&(1<<i)) x=up[x][i];
		return x;
	};
	auto liftv=[&](int x, int k, pll &c) {
		FOR(19) if (k&(1<<i)) c=merge(c, trav1[x][i], trav2[x][i]), x=up[x][i];
	};
	auto lca=[&](int a, int b) {
		a=lift(a, d[a]-min(d[a], d[b]));
		b=lift(b, d[b]-min(d[a], d[b]));
		if (a==b) return a;
		FOR(i, 18, -1, -1) if (up[a][i]!=up[b][i]) a=up[a][i], b=up[b][i];
		return up[a][0];
	};
	int q; read(q);
	FOR(q) {
		read(x, y); --x, --y;
		pll l=x&1 ? RI : LI;
		pll r=y&1 ? RI : LI;
		x/=2, y/=2;
		int u=lca(x, y);
		liftv(x, d[x]-d[u], l);
		liftv(y, d[y]-d[u], r);
		print(min(min(l.f+r.f, l.s+r.s), min(l.f+r.s, l.s+r.f)+w[u]));
	}
}

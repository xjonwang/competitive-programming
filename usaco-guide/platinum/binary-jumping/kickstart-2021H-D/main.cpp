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

#define MOD 1000000007
#define INV 142857001
#define PROB 1000000

void dfs(const vt<vt<int>> &adj, vt<int> &d, vt<vt<int>> &up, const vt<pll> &val, vt<pll> &prob, int v, int p=-1) {
	if (p!=-1) {
		d[v]=d[p]+1;
		prob[v]={(val[v].f*prob[p].f+val[v].s*prob[p].s)%MOD, ((PROB-val[v].f)*prob[p].f+(PROB-val[v].s)*prob[p].s)%MOD};
	}
	d[v]=p!=-1 ? d[p]+1 : 0;
	up[v][0]=p;
	EACH(u, adj[v]) {
		dfs(adj, d, up, val, prob, u, v);
	}
}

struct pd {
	ll xx, xo, ox, oo;
	pd() : xx(1), xo(0), ox(0), oo(1) {};
	pd(ll xx, ll ox) : xx(xx), xo(PROB-xx), ox(ox), oo(PROB-ox) {};
	pd(ll xx, ll xo, ll ox, ll oo) : xx(xx), xo(xo), ox(ox), oo(oo) {};
};

pd merge(pd l, pd r) {
	return {
		(r.xx*l.xx+r.xo*l.ox)%MOD,
		(r.xx*l.xo+r.xo*l.oo)%MOD,
		(r.ox*l.xx+r.oo*l.ox)%MOD,
		(r.ox*l.xo+r.oo*l.oo)%MOD
	};
}

ll modexp(int x, int e) {
	if (e==0) return 1;
	ll u=modexp(x, e/2);
	u=u*u%MOD;
	if (e&1) u=u*x%MOD;
	return u;
}

void solve(int t) {
	int n, m, k, x, y, z; read(n, m, k);
	vt<pll> val(n), prob(n);
	vt<vt<int>> adj(n);
	vt<int> d(n);
	vt<vt<int>> up(n, vt<int>(18, -1));
	vt<vt<pd>> trav(n, vt<pd>(18));
	FOR(i, 1, n) {
		read(x, y, z); --x;
		up[i][0]=x;
		adj[x].pb(i);	
		val[i]={y, z};
	}
	d[0]=0;
	prob[0]={k, PROB-k};
	dfs(adj, d, up, val, prob, 0);
	FOR(n) trav[i][0]={val[i].f, val[i].s};
	FOR(i, 1, 18) {
		FOR(j, n) {
			if (up[j][i-1]!=-1) {
				up[j][i]=up[up[j][i-1]][i-1];
				trav[j][i]=merge(trav[j][i-1], trav[up[j][i-1]][i-1]);
			}
		}
	}
	auto lift=[&](int x, int k) {
		FOR(18) if (k&(1<<i)) x=up[x][i];
		return x;
	};
	auto liftv=[&](int x, int k) {
		pd ret{};
		FOR(18) if (k&(1<<i)) ret=merge(ret, trav[x][i]), x=up[x][i];
		return ret;
	};
	auto lca=[&](int a, int b) {
		a=lift(a, d[a]-min(d[a], d[b]));
		b=lift(b, d[b]-min(d[a], d[b]));
		if (a==b) return a;
		FOR(i, 17, -1, -1) if (up[a][i]!=up[b][i]) a=up[a][i], b=up[b][i];
		return up[a][0];
	};
	vt<int> ans(m);
	FOR(m) {
		read(x, y); --x, --y;
		int u=lca(x, y);
		pd l=liftv(x, d[x]-d[u]);
		pd r=liftv(y, d[y]-d[u]);
		ll p=prob[u].f*l.xx%MOD*r.xx%MOD + prob[u].s*l.ox%MOD*r.ox%MOD;
		ans[i]=modexp(INV, d[x]+d[y]-d[u]+1)*p%MOD;
	}
	cout << "Case #" << t << ": ";
	print(ans);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("/home/xjonwang/cp/usaco-guide/platinum/binary-jumping/kickstart-2021H-D/test_set_2/ts2_input.txt", "r", stdin);
	freopen("/home/xjonwang/cp/usaco-guide/platinum/binary-jumping/kickstart-2021H-D/test_set_2/ts2.txt", "w", stdout);
	int t; read(t);
	FOR(t) solve(i+1);
}

#include "werewolf.h"

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
#define eb emplace_back
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

struct KRT {
	int n, h, timer;
	vt<int> dsu, idx, tin, tout, depth;
	vt<vt<int>> adj, up;
	vt<bool> vis;
	KRT(int n) : n(n), h(n), timer(0), dsu(2*n-1), adj(2*n-1), up(2*n-1, vt<int>(19, -1)), idx(2*n-1, INT_MAX), tin(2*n-1), tout(2*n-1), depth(2*n-1), vis(2*n-1, 0) {
		iota(dsu.begin(), dsu.begin()+n, 0);
	}
	int get(int u) {
		return u==dsu[u] ? u : dsu[u]=get(dsu[u]);
	}
	void ae(int u, int v, int i) {
		u=get(u), v=get(v);
		if (u==v) return;
		dsu[h]=h;
		dsu[u]=dsu[v]=h;
		adj[h].pb(u), adj[h].pb(v);
		up[u][0]=up[v][0]=h;
		idx[h]=i;
		h++;
	}
	void dfs(int v) {
		vis[v]=1;
		tin[v]=timer++;
		EACH(u, adj[v]) {
			depth[u]=depth[v]+1;
			dfs(u);
		}
	}
	void gen() {
		FOR(j, 1, 19) FOR(i, 2*n-1) if (up[i][j-1]!=-1) up[i][j]=up[up[i][j-1]][j-1];
		FOR(i, 2*n-2, -1, -1) {
			if (!vis[i]) {
				depth[i]=0;
				dfs(i);
			}
		}
	}
	int lift(int u, int k) {
		FOR(19) if (k&(1<<i)) u=up[u][i];
		return u;
	}
	int lca(int a, int b) {
		a=lift(a, depth[a]-min(depth[a], depth[b]));
		b=lift(b, depth[b]-min(depth[a], depth[b]));
		if (a==b) return a;
		FOR(i, 18, -1, -1) if (up[a][i]!=up[b][i]) a=up[a][i], b=up[b][i];
		return up[a][0];
	}
	int query(int a, int b) {
		int c=lca(a, b);
		return c!=-1 ? idx[c] : -1;
	}
};

struct DSU {
	vt<int> e;
	vt<set<pii>> tin;
	DSU(int n, span<int> a) : e(n, -1), tin(n) {
		FOR(n) tin[i].insert({a[i], i});
	}
	int get(int x) { return e[x]<0 ? x : e[x]=get(e[x]); }
	int size(int x) { return e[x]<0 ? -e[x] : size(e[x]); }
	bool unite(int x, int y) {
		x=get(x), y=get(y);
		if (x==y) return false;
		if (e[x]>e[y]) swap(x, y);
		e[x]+=e[y];
		e[y]=x;
		if (sz(tin[y])>sz(tin[x])) swap(tin[x], tin[y]);
		tin[x].insert(all(tin[y]));
		tin[y].clear();
		return true;
	}
};

struct query {
	int st, en, l, r, i;
};

vt<int> check_validity(int n, vt<int> x, vt<int> y,
					   vt<int> S, vt<int> E,
					   vt<int> L, vt<int> R) {
	int m=sz(x);
	vt<pii> e(m);
	FOR(m) e[i]={x[i], y[i]};
	sort(all(e), [](const pii& a, const pii& b) { return a.f>b.f; });
	KRT krt(n);
	for (auto &[l, r] : e) {
		if (l>r) swap(l, r);
		krt.ae(l, r, l);
	}
	krt.gen();
	int k=sz(S);
	vt<query> q(k);
	FOR(k) q[i]={S[i], E[i], L[i], R[i], i};
	sort(all(e), [](const pii& a, const pii& b) { return a.s<b.s; });
	sort(all(q), [](const query& a, const query& b) { return a.r<b.r; });
	int p=0;
	vt<int> ans(k);
	DSU dsu(n, span(krt.tin).subspan(0, n));
	for (auto &[st, en, bl, br, i] : q) {
		for (; p<m && e[p].s<=br; p++) dsu.unite(e[p].f, e[p].s);
		set<pii>& tins=dsu.tin[dsu.get(en)];
		auto it=tins.lower_bound(make_pair(krt.tin[st], st));
		int a=-1;
		if (it!=tins.end()) umax(a, krt.query(it->s, st));
		if (it!=tins.begin()) umax(a, krt.query(prev(it)->s, st));
		ans[i]=(a>=bl);
	}
	return ans;
}

/*
6 5 1
5 3
3 0
0 2
2 4
4 1
5 1 2 4
*/

#include "swap.h"

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
#define rsz resize
#define asn assign
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
	int n, m, h;
	vt<bool> sw;
	vt<int> dsu, w, depth;
	vt<vt<int>> adj, up;
	void init(int a_n, int a_m) {
		n=h=a_n;
		m=a_m;
		dsu.rsz(n+m), adj.rsz(n+m), up.asn(n+m, vt<int>(19, -1)), w.rsz(n+m), sw.asn(n+m, 0), depth.rsz(n+m);
		iota(dsu.begin(), dsu.begin()+n, 0);
	}
	int get(int u) {
		return u==dsu[u] ? u : dsu[u]=get(dsu[u]);
	}
	void ae(int u, int v, int i, bool deg3) {
		u=get(u), v=get(v);
		if (u==v) {
			dsu[h]=dsu[u]=h;
			adj[h].pb(u);
			up[u][0]=h;
			w[h]=i;
			sw[h]=1;
			h++;
		} else {
			dsu[h]=dsu[u]=dsu[v]=h;
			adj[h].pb(u), adj[h].pb(v);
			up[u][0]=up[v][0]=h;
			w[h]=i;
			sw[h]=sw[u]||sw[v]||deg3;
			h++;
		}
	}
	void dfs(int v) {
		EACH(u, adj[v]) {
			depth[u]=depth[v]+1;
			dfs(u);
		}
	}
	void gen() {
		FOR(j, 1, 19) FOR(i, n+m) if (up[i][j-1]!=-1) up[i][j]=up[up[i][j-1]][j-1];
		depth[n+m-1]=0; dfs(n+m-1);
	}
	int lift(int x, int k) {
		FOR(19) if (k&(1<<i)) x=up[x][i];
		return x;
	}
	int lca(int a, int b) {
		a=lift(a, depth[a]-min(depth[a], depth[b]));
		b=lift(b, depth[b]-min(depth[a], depth[b]));
		if (a==b) return a;
		FOR(i, 18, -1, -1) if (up[a][i]!=up[b][i]) a=up[a][i], b=up[b][i];
		return up[a][0];
	}
	int trav(int u) {
		if (sw[u]) return u;
		FOR(i, 18, -1, -1) if (up[u][i]!=-1 && !sw[up[u][i]]) u=up[u][i];
		return up[u][0];
	}
	int query(int a, int b) {
		int c=lca(a, b);
		c=trav(c);
		return c!=-1 ? w[c] : -1;
	}
};

struct edge {
	int u, v, w;
};

KRT krt;

void init(int n, int m,
          std::vector<int> U, std::vector<int> V, std::vector<int> W) {
	krt.init(n, m);
	vt<edge> e(m);
	FOR(m) e[i]={U[i], V[i], W[i]};
	sort(all(e), [](const edge& a, const edge& b) { return a.w<b.w; });
	vt<int> deg(n, 0);
	for (auto &[u, v, w] : e) krt.ae(u, v, w, (++deg[u]>=3 || ++deg[v]>=3));
	krt.gen();
}

int getMinimumFuelCapacity(int x, int y) {
	return krt.query(x, y);
}

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

int n, k;
vt<vt<int>> adj;
vt<pii> edges;
vt<int> par, depth;
vt<vt<ll>> sub;
ll cnt;

struct DSU {
	int n;
	vt<int> e, r;
	void init(int a) {
		n=a;
		e.asn(n, -1);
		r.rsz(n);
		iota(all(r), 0);
	}
	int get(int x) { return e[x]<0 ? x : e[x]=get(e[x]); }
	int root(int x) { return r[get(x)]; }
	bool sameSet(int a, int b) { return get(a)==get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) {
		x=get(x), y=get(y); if (x==y) return 0;
		if (e[x] > e[y]) swap(x,y);
		if (depth[r[y]]<depth[r[x]]) r[x]=r[y];
		e[x] += e[y]; e[y] = x; return 1;
	}
};

void dfs1(int v) {
	EACH(u, adj[v]) {
		if (u==par[v]) continue;
		depth[u]=depth[v]+1;
		par[u]=v;
		dfs1(u);
	}
}

void dfs2(int v, ll& cnt1, ll& cnt2) {
	EACH(u, adj[v]) {
		if (u==par[v]) continue;
		FOR(j, 1, k) {
			int l1=j-1, l2=k-j;
			cnt2+=sub[u][l1]*(sub[v][l2]-sub[u][l2-1]);
		}
		cnt1+=sub[u][k-1]*sub[v][0];
		dfs2(u, cnt1, cnt2);
	}
}

DSU dsu;

void query(int v) {
	dsu.unite(v, par[v]);
	vt<int> diff(k+1);
	diff[0]=sub[v][0];
	FOR(i, 1, k+1) diff[i]+=sub[v][i]-sub[v][i-1];
	FOR(k+1) {
		if (par[v]==-1) break;
		int u=dsu.root(par[v]);
		FOR(j, i, k+1) {
			sub[u][j]+=diff[j-i];
		}
		FOR(j, k+1-i) {
			ll dup=(i==0 ? sub[v][k-j-i] : (k-j-i>0 ? sub[v][k-j-i-1] : 0));
			cnt+=diff[j]*(sub[u][k-j-i]-dup);
		}
		v=u;
	}
	print(cnt);
}

int main() {
	read(n, k);
	adj.rsz(n), edges.rsz(n-1), par.rsz(n), depth.rsz(n);
	sub.asn(n, vt<ll>(k+1, 0));
	FOR(n-1) {
		int x, y; read(x, y); --x, --y;
		adj[x].pb(y), adj[y].pb(x);
		edges[i]={x, y};
	}
	depth[0]=0;
	par[0]=-1;
	dfs1(0);
	FOR(n-1) {
		if (par[edges[i].f]==edges[i].s) swap(edges[i].f, edges[i].s);
	}
	FOR(n) {
		for (int j=0, v=i; j<=k && v!=-1; j++, v=par[v]) sub[v][j]++;
	}
	ll cnt1=0, cnt2=0;
	dfs2(0, cnt1, cnt2);
	cnt = cnt1+cnt2/2;
	dsu.init(n);
	FOR(n-1) {
		int x; read(x);
		x=(x+cnt)%(n-1);
		query(edges[x].s);
	}
}

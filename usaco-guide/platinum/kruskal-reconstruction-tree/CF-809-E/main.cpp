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
	int n, h;
	vt<int> dsu, idx;
	vt<vt<int>> adj;
	KRT(int n) : n(n), h(n), dsu(2*n-1), adj(2*n-1), idx(n-1) {
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
		idx[h-n]=i;
		h++;
	}
};

template<typename T>
struct RMQ {
	int level(int x) { return 31-__builtin_clz(x); }
	vt<T> v; vt<vt<int>> jmp;
	int cmb(int a, int b) {
		return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); }
	void init(const vt<T>& _v) {
		v = _v; jmp = {vt<int>(sz(v))};
		iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= sz(v); ++j) {
			jmp.pb(vt<int>(sz(v)-(1<<j)+1));
			FOR(i,sz(jmp[j])) jmp[j][i] = cmb(jmp[j-1][i],
				jmp[j-1][i+(1<<(j-1))]);
		}
	}
	int index(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return cmb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
	T query(int l, int r) { return v[index(l,r)]; }
};

struct LCA {
	int N; vt<vt<int>> adj;
	vt<int> depth, pos, par, rev;
	vt<pii> tmp1; RMQ<pii> r1;
	vt<int> tmp2; RMQ<int> r2, r3;
	void init(int _N) { N = _N; adj.resize(N); 
		depth = pos = par = rev = tmp2 = vt<int>(N); }
	void ae(int x, int y) { adj[x].pb(y), adj[y].pb(x); }
	void dfs(int x) {
		pos[x] = sz(tmp1); tmp1.eb(depth[x],x); 
		tmp2[x]=pos[x];
		EACH(y,adj[x]) if (y != par[x]) {
			depth[y] = depth[par[y]=x]+1, dfs(y);
			tmp1.eb(depth[x],x); }
	}
	void gen(int R = 0) {
		par[R] = R; dfs(R); r1.init(tmp1);
		r2.init(tmp2);
		EACH(t, tmp2) t*=-1;
		r3.init(tmp2);
	}
	int lca(int u, int v){
		u = pos[u], v = pos[v]; if (u > v) swap(u,v);
		return r1.query(u,v).s; }
	int dist(int u, int v) {
		return depth[u]+depth[v]-2*depth[lca(u,v)]; }
	vt<pii> compress(vt<int> S) {
		auto cmp = [&](int a, int b) { return pos[a] < pos[b]; };
		sort(all(S),cmp); FOR(i,sz(S)-1,-1,-1) S.pb(lca(S[i],S[i+1]));
		sort(all(S),cmp); S.erase(unique(all(S)),end(S));
		vt<pii> ret{{0,S[0]}}; FOR(i,sz(S)) rev[S[i]] = i;
		FOR(i,1,sz(S)) ret.eb(rev[lca(S[i-1],S[i])],S[i]);
		return ret;
	}
};


void solve() {
	int n, m, q; read(n, m, q);
	KRT krt(n);
	FOR(m) {
		int x, y; read(x, y);
		krt.ae(--x, --y, i);
	}
	LCA lca; lca.init(2*n-1);
	FOR(u, 2*n-1) EACH(v, krt.adj[u]) lca.ae(u, v);
	lca.gen(2*n-2);
	vt<int> ans(q);
	FOR(q) {
		int x, y; read(x, y); --x, --y;
		int l=lca.r2.query(x, y);
		int r=-lca.r3.query(x, y);
		int a=lca.r1.query(l, r).s;
		ans[i]=a<n ? 0 : krt.idx[a-n]+1;
	}
	print(ans);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}
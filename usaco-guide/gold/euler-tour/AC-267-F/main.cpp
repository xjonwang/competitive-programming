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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			FOR(j, 0, sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b);
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct FT {
	vt<ll> v;
	FT(int n) : v(n) {}
	FT(vt<ll>& va) : v(sz(va)) {
		v[0]+=va[0]; v[1]+=v[0];
		FOR(i, 1, sz(va)) {
			v[i]+=va[i]-va[i-1];
			int r=i|(i+1);
			if (r<sz(va)) v[r]+=v[i];
		}
	}
	void update(int pos, ll dif) {
		for (; pos < sz(v); pos |= pos + 1)v[pos] += dif;
	}
	ll query(int pos) {
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += v[pos-1];
		return res;
	}
};

struct edge {
	int u, v, w;
};

vt<edge> e;
vt<vt<pii>> adj;
vt<int> fi, ti, to, d1;
vt<pii> lca;
vt<ll> d2;
int t;

void dfs1(int v, int d, int p=-1) {
	d1[v]=d; lca[t]={d, v}; fi[v]=t; t++;
	for (auto& [u, c] : adj[v]) {
		if (u==p) continue;
		dfs1(u, d+1, v);
		lca[t++]={d, v};
	}
}

void dfs2(int v, ll d, int p=-1) {
	d2[t]=d; ti[v]=t++;
	for (auto& [u, c] : adj[v]) {
		if (u==p) continue;
		dfs2(u, d+c, v);
	}
	to[v]=t;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, q, x, y, z; read(n);
	adj.resize(n), e.resize(n-1), fi.resize(n), ti.resize(n), to.resize(n), lca.resize(2*n-1), d1.resize(n), d2.resize(n);
	FOR(n-1) {
		read(x, y, z); --x, --y;
		e[i]={x, y, z};
		adj[x].pb({y, z});
		adj[y].pb({x, z});
	}
	dfs1(0, 0);
	t=0; dfs2(0, 0);
	RMQ rmq(lca);
	FT ft(d2);
	read(q);
	FOR(q) {
		read(x);
		if (x==1) {
			read(x, y); --x;
			auto [u, v, w]=e[x];
			if (d1[v]<d1[u]) swap(u, v);
			ft.update(ti[v], y-w);
			ft.update(to[v], w-y);
			e[x].w=y;
		} else {
			read(x, y); --x, --y;
			print(ft.query(ti[x]+1)+ft.query(ti[y]+1)-2*ft.query(ti[rmq.query(min(fi[x], fi[y]), max(fi[x], fi[y])+1).s]+1));
		}
	}
}
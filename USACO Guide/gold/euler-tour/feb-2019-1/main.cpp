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

struct RUPX {
	vt<ll> v;
	RUPX(int n) : v(n) {}
	RUPX(vt<ll>& va) : v(sz(va)) {
		v[0]^=va[0], v[1]^=v[0];
		FOR(i, 1, sz(va)) {
			v[i]^=va[i]^va[i-1];
			int r=i|(i+1);
			if (r<sz(v)) v[r]^=v[i];
		}
	}
	void update(int pos, ll dif) {
		for (; pos < sz(v); pos |= pos + 1) v[pos]^=dif;
	}
	void range_update(int l, int r, ll dif) {
		update(l, dif);
		update(r, dif);
	}
	ll query(int pos) {
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res^=v[pos-1];
		return res;
	}
};

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
	void update(int pos, ll dif) {
		for (; pos < sz(v); pos |= pos + 1)v[pos] += dif;
	}
	ll query(int pos) {
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += v[pos-1];
		return res;
	}
};

using T=pair<pii, int>;
vt<vt<int>> adj;
vt<int> ti, to;
vt<pii> vis;
int t;

void dfs(int v, int d, int p=-1) {
	vis[t]={d, v};
	umin(ti[v], t++);
	EACH(u, adj[v]) {
		if (u==p) continue;
		dfs(u, d+1, v);
		vis[t++]={d, v};
	}
	to[v]=t;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("milkvisits.in", "r", stdin);
	freopen("milkvisits.out", "w", stdout);
	int n, m, x, y, z; read(n, m);
	adj.resize(n), ti.resize(n, INT_MAX), to.resize(n), vis.resize(2*n+1, {INT_MAX, INT_MAX});
	vt<vt<int>> t(n);
	FOR(n) read(x), t[--x].pb(i);
	FOR(n-1) {
		read(x, y); --x, --y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	vt<vt<T>> q(n);
	FOR(m) {
		read(x, y, z); --x, --y, --z;
		q[z].pb({{x, y}, i});
	}
	dfs(0, 0);
	RMQ rmq(vis);
	FT ft(2*n-1);
	string ans(m, ' ');
	FOR(n) {
		if (sz(q[i])==0) continue;
		EACH(v, t[i]) ft.update(ti[v], 1), ft.update(to[v], -1);
		EACH(a, q[i]) {
			int lca=rmq.query(min(ti[a.f.f], ti[a.f.s]), max(ti[a.f.f], ti[a.f.s])+1).s;
			ans[a.s]=ft.query(ti[a.f.f]+1)+ft.query(ti[a.f.s]+1)-2*ft.query(ti[lca]) ? '1' : '0';
		}
		EACH(v, t[i]) ft.update(ti[v], -1), ft.update(to[v], 1);
	}
	print(ans);
}
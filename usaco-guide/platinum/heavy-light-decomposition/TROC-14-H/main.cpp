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

struct ST {
	int n, h;
	vt<int> v;
	vt<bool> d;
	ST(int a) : n(1) {
		while (n<a) n<<=1;
		h=32-__builtin_clz(n);
		v.assign(2*n, 0);
		d.assign(n, 0);
	};
	void apply(int i, bool x) {
		v[i]=size(i)-v[i];
		if (i<n) d[i]=d[i]^x;
	}
	int size(int i) {
		return 1<<(__builtin_clz(i)-__builtin_clz(n));
	}
	void build(int i) {
		for (; i>>=1;) v[i]=d[i] ? size(i)-(v[i<<1]+v[i<<1|1]) : v[i<<1]+v[i<<1|1];
	}
	void propagate(int i) {
		FOR(j, h-1, 0, -1) {
			int t=i>>j;
			if (d[t]) {
				apply(t<<1, d[t]);
				apply(t<<1|1, d[t]);
				d[t]=0;
			}
		}
	}
	void modify(int l, int r) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		propagate(l0);
		propagate(r0);
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) apply(l++, 1);
			if (r&1) apply(--r, 1);
		}
		build(l0);
		build(r0);
	}
	int query(int l, int r) {
		l+=n, r+=n;
		propagate(l);
		propagate(r-1);
		int ret=0;
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) ret+=v[l++];
			if (r&1) ret+=v[--r];
		}
		return ret;
	}
};

ll c2(ll x) { return x*(x-1)/2; }

struct HLD {
	int n, st, ti;
	ST seg;
	vt<vt<int>> adj;
	vt<int> d, size, par, pos, rpos, end, chain; 
	vt<ll> under;
	HLD(int n, int st=0) : n(n), st(st), ti(0), seg(n), adj(n), d(n), size(n), par(n), pos(n), end(n), chain(n), under(n, 0) {};
	void ae(int x, int y) {
		adj[x].pb(y), adj[y].pb(x);
	}		
	void init(const vt<int> &v) {
		d[st]=par[st]=0; dfs1(st);
		chain[st]=st; dfs2(st);
		FOR(sz(v)) if (v[i]) seg.modify(pos[i], pos[i]+1);
		FOR(n) {
			FOR(j, 1, sz(adj[i])) under[i]+=c2(seg.query(pos[adj[i][j]], end[adj[i][j]]));
		}
	};
	void dfs1(int v) {
		size[v]=1;
		EACH(u, adj[v]) {
			par[u]=v, d[u]=d[v]+1;
			adj[u].erase(find(all(adj[u]), v));
			dfs1(u);
			size[v]+=size[u];
			if (size[u]>size[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfs2(int v) {
		pos[v]=ti++, rpos.pb(v);
		FOR(min(1, sz(adj[v]))) chain[adj[v][i]]=chain[v];
		FOR(i, 1, sz(adj[v])) chain[adj[v][i]]=adj[v][i];
		EACH(u, adj[v]) dfs2(u);
		end[v]=ti;
	}
	void modify(int v) {
		int v0=v;
		map<int, int> ocnt;
		while (d[chain[v]]) {
			v=chain[v];
			ocnt[v]=seg.query(pos[v], end[v]);
			v=par[v];
		}
		v=v0;
		for (; d[chain[v]]; v=par[chain[v]]) {
			seg.modify(pos[chain[v]], pos[v]+1);
		}
		seg.modify(pos[chain[v]], pos[v]+1);
		v=v0;
		while (d[chain[v]]) {
			v=chain[v];
			under[par[v]]+=c2(seg.query(pos[v], end[v]))-c2(ocnt[v]);
			v=par[v];
		}
	}
	ll query(int v) {
		ll ans=c2(seg.query(pos[v], end[v]))-under[v];
		if (sz(adj[v])) {
			ans-=c2(seg.query(pos[adj[v][0]], end[adj[v][0]]));
		}
		return ans;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, x, y; read(n, m);
	vt<int> v(n); read(v);
	HLD hld(n);
	FOR(n-1) {
		read(x, y);
		hld.ae(--x, --y);
	}
	hld.init(v);
	FOR(m) {
		read(x);
		switch (x) {
		case 1:
			read(x);
			hld.modify(--x);
			break;
		case 2:
			read(x);
			print(hld.query(--x));
			break;
		}
	}
}
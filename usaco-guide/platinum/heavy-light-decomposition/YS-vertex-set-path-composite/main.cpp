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

#define MOD 998244353

struct ST {
	int n;
	vt<pll> vl, vr;
	ST(int n) : n(n), vl(2*n, {1, 0}), vr(2*n, {1, 0}) {};
	pii combine(pll l, pll r) {
		return {l.f*r.f%MOD, (l.s+l.f*r.s)%MOD};
	}
	void modify(int i, pll x) {
		for (i+=n, vl[i]=vr[i]=x; i>>=1;) vl[i]=combine(vl[i*2], vl[i*2+1]), vr[i]=combine(vr[i*2+1], vr[i*2]);	
	}
	pll queryl(int l, int r) {
		pll retl={1, 0}, retr={1, 0};
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) retl=combine(retl, vl[l++]);
			if (r&1) retr=combine(vl[--r], retr); 
		}
		return combine(retl, retr);
	}
	pll queryr(int l, int r) {
		pll retl={1, 0}, retr={1, 0};
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) retl=combine(vr[l++], retl);
			if (r&1) retr=combine(retr, vr[--r]); 
		}
		return combine(retr, retl);
	}
};

struct HLD {
	int n, st, ti;
	ST seg;
	vt<vt<int>> adj;
	vt<int> d, size, par, pos, rpos, end, chain; 
	HLD(int n, int st=0) : n(n), st(st), ti(0), seg(n), adj(n), d(n), size(n), par(n), pos(n), end(n), chain(n) {};
	void ae(int x, int y) {
		adj[x].pb(y), adj[y].pb(x);
	}		
	void init() {
		d[st]=par[st]=0; dfs1(st);
		chain[st]=st; dfs2(st);
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
	pll query(int u, int v) {
		pll retl={1, 0}, retr={1, 0};
		while (chain[u]!=chain[v]) {
			if (d[chain[u]]>d[chain[v]]) {
				retl=seg.combine(seg.queryl(pos[chain[u]], pos[u]+1), retl);
				u=par[chain[u]];
			} else {
				retr=seg.combine(retr, seg.queryr(pos[chain[v]], pos[v]+1));
				v=par[chain[v]];
			}
		}
		if (d[u]>d[v]) {
			retl=seg.combine(seg.queryl(pos[v], pos[u]+1), retl);
		} else {
			retr=seg.combine(retr, seg.queryr(pos[u], pos[v]+1));
		}
		return seg.combine(retr, retl);
	}
	void modify(int v, pll x) {
		seg.modify(pos[v], x);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, x, y, z; read(n, m);
	vt<pii> v(n); read(v);
	HLD hld(n);
	FOR(n-1) {
		read(x, y);
		hld.ae(x, y);
	}
	hld.init();
	FOR(n) hld.modify(i, v[i]);
	FOR(m) {
		read(x);
		switch (x) {
		case 0:
			read(x, y, z);
			hld.modify(x, {y, z});
			break;
		case 1:
			read(x, y, z);
			pll t=hld.query(x, y);
			print((t.f*z+t.s)%MOD);
			break;
		}
	}
}
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

template<int(*AssocOp)(int, int), int Init>
struct ST {
	int n, h;
	vt<int> v;
	ST(int n) : n(n), v(2*n, Init) {};
	void modify(int i, int x) {
		for (v[i+=n]=x; i/=2;) v[i]=AssocOp(v[i*2], v[i*2+1]);
	}
	int query(int l, int r) {
		int retl=Init, retr=Init;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) retl=AssocOp(retl, v[l++]);
			if (r&1) retr=AssocOp(v[--r], retr);
		}
		return AssocOp(retl, retr);
	}
};

int tmin(int a, int b) { return min(a, b); }
int tmax(int a, int b) { return max(a, b); }

struct HLD {
	int n, st, ti;
	ST<tmin, INT_MAX> mi;
	ST<tmax, INT_MIN> ma;
	vt<vt<int>> adj;
	vt<int> d, size, par, pos, rpos, chain; 
	vt<bool> tog;
	HLD(int n, int st=0) : n(n), st(st), ti(0), mi(n), ma(n), adj(n), d(n), size(n), par(n), pos(n), chain(n), tog(n, 0) {};
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
	}
	int query(int u, int v) {
		int l=INT_MIN, r=INT_MAX;
		while (chain[u]!=chain[v]) {
			if (d[chain[u]]>d[chain[v]]) {
				umax(l, ma.query(pos[chain[u]], pos[u]+1)); 
				u=par[chain[u]];
			} else {
				umin(r, mi.query(pos[chain[v]], pos[v]+1)); 
				v=par[chain[v]];
			}
		}
		if (d[u]<d[v]) {
			umin(r, mi.query(pos[u], pos[v]+1));
		} else {
			umax(l, ma.query(pos[v], pos[u]+1));
		}
		return (l!=INT_MIN) ? rpos[l]+1 : (r!=INT_MAX) ? rpos[r]+1 : -1;
	}
	void modify(int v) {
		if (tog[v]=!tog[v]) {
			mi.modify(pos[v], pos[v]);
			ma.modify(pos[v], pos[v]);
		} else {
			mi.modify(pos[v], INT_MAX);
			ma.modify(pos[v], INT_MIN);
		}
	}

};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, x, y; read(n, m);
	HLD hld(n);
	FOR(n-1) {
		read(x, y);
		hld.ae(--x, --y);
	}
	hld.init();
	FOR(m) {
		read(x);
		switch (x) {
		case 0:
			read(y);
			hld.modify(--y);
			break;
		case 1:
			read(y);
			print(hld.query(0, --y));
			break;
		}
	}
}
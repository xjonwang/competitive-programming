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

struct ST {
	int n, h; vt<ll> v, d1, d2;
	void init(int a) {
		n=1;
		while (n<a) n*=2;
		h=32-__builtin_clz(n);
		v.assign(2*n, 0);
		d1.assign(n, 0), d2.assign(n, 0);
	}
	int size(int i) {
		return 1<<(h-(32-__builtin_clz(i)));
	}
	ll calc(int i) {
		if (i>=n) return v[i];
		return (d2[i] ? d2[i]*size(i) : v[i<<1]+v[i<<1|1])+d1[i]*size(i);
	}
	void apply_delta(int i, ll d) {
		v[i]+=d*size(i);
		if (i<n) d1[i]+=d;
	}
	void apply_set(int i, ll x) {
		v[i]=x*size(i);
		if (i<n) d2[i]=x, d1[i]=0;
	}
	void push(int i) {
		if (d2[i]) apply_set(i<<1, d2[i]), apply_set(i<<1|1, d2[i]);
		if (d1[i]) apply_delta(i<<1, d1[i]), apply_delta(i<<1|1, d1[i]);
		d1[i]=d2[i]=0;
	}
	void propagate(int i) {
		for (int j=h; j>0; j--) push(i>>j);
	}
	void build(int i) {
		while (i>1) i>>=1, v[i]=calc(i);
	}
	void modify(int l, int r, ll d) {
		int l0=l+n, r0=r+n-1;
		propagate(l0), propagate(r0);
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) apply_delta(l++, d);
			if (r&1) apply_delta(--r, d);
		}
		build(l0), build(r0);
	}
	void set(int l, int r, ll x) {
		int l0=l+n, r0=r+n-1;
		propagate(l0), propagate(r0);
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) apply_set(l++, x);
			if (r&1) apply_set(--r, x);
		}
		build(l0), build(r0);
	}
	ll query(int l, int r) {
		ll ret=0;
		propagate(l+n), propagate(r+n-1);
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) ret+=calc(l++);
			if (r&1) ret+=calc(--r);
		}
		return ret;
	}
};

struct HLD {
	int n, k;
	vt<vt<int>> adj;
	vt<pii> edges;
	vt<int> par, root, depth, siz, pos;
	int ti;
	ST color;
	vt<ST> v1;

	int h;
	vt<vt<int>> up, val;

	ll cnt;

	void ae(int x, int y) {
		adj[x].pb(y);
		adj[y].pb(x);
		edges.pb({x, y});
	}

	void init(int a_n, int a_k) {
		n=a_n, k=a_k;
		adj.rsz(n), par.rsz(n), root.rsz(n), depth.rsz(n), siz.rsz(n), pos.rsz(n);	
		v1.rsz(k+1);
		FOR(k+1) v1[i].init(n);
		color.init(n);
		h = ceil(log(n));
		up.assign(h, vt<int>(n, -1)), val.assign(h, vt<int>(n, 0));
	}

	void gen() {
		par[0]=depth[0]=ti=0;
		dfsSz(0);
		root[0]=0;
		dfsHld(0);
		FOR(n-1) {
			if (par[edges[i].f]==edges[i].s) swap(edges[i].f, edges[i].s);
		}

		up[0][0]=-1;
		FOR(i, 1, n) up[0][i]=par[i];
		FOR(j, 1, h) {
			FOR(i, n) {
				if (up[j-1][i]!=-1) up[j][i]=up[j-1][up[j-1][i]];
			}
		}
		
		FOR(n) {
			int v=i;
			FOR(j, k+1) {
				v1[j].modify(v, v+1, 1);
				if (v==par[v]) break;
				v=par[v];
			}
		}
		cnt=0;
		dfs1(0);
	}

	void dfsSz(int v) {
		siz[v]=1;
		EACH(u, adj[v]) {
			par[u]=v;
			depth[u]=depth[v]+1;
			adj[u].erase(find(all(adj[u]), v));
			dfsSz(u); siz[v]+=siz[u];
			if (siz[u]>siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}

	void dfsHld(int v) {
		pos[v]=ti++;
		EACH(u, adj[v]) {
			root[u]=(u==adj[v][0] ? root[v] : u);
			dfsHld(u);
		}
	}

	template<typename Op>
	void processPath(int x, int y, Op op) {
		for (; root[x]!=root[y]; y=par[root[y]]) {
			if (depth[root[x]]>depth[root[y]]) swap(x, y);
			op(pos[root[y]], pos[y]);
		}
		if (depth[x]>depth[y]) swap(x, y);
		op(pos[x], pos[y]);
	}

	void modifyColor(int x, int y, int v) {
		processPath(x, y, [this, &v](int l, int r) { color.modify(l, r, v); });
	}

	ll queryColor(int x, int y) {
		ll ret=0;
		processPath(x, y, [this, &ret](int l, int r) { ret+=color.query(l, r); });
		return ret;
	}

	void dfs1(int v) {
		EACH(u, adj[v]) {
			FOR(j, 1, k+1) {
				int l1=j-1, l2=k-j;
				cnt+=v1[l1].query(u, u+1)*(v1[l2].query(v, v+1)-(l2>0 ? v1[l2-0].query(u, u+1) : 0));
			}
			dfs1(u);
		}
	}

	int nextRed(int v) {
		FOR(j, h-1, -1, -1) {
			if (up[v][j]!=-1 && queryColor(v, up[v][j])==1<<j) v=up[v][j];
		}
		return v;
	}

	ll update(int eidx) {
		int v=edges[eidx].s;
		vt<int> upexp(k+1);
		vt<int> subexp(k+1);
		upexp[0]=0;
		FOR(i, 1, k+1) upexp[i]=v1[i-1].query(v, v+1);
		FOR(k+1) subexp[i]=v1[i].query(v, v+1);
		modifyColor(v, par[v], 1);
		ll diff=0;
		FOR(k+1) {
			int u=nextRed(v);
			processPath(v, u, [this, &upexp, &subexp, i, v, u](int l, int r) {
				FOR(j, i, k+1) {
					v1[j].modify(v, u, subexp[j-i]-upexp[j-i]);
				}
			});
		}
	}

	void debug() {
		FOR(k+1) {
			cout << "v1 " << i << endl;
			FOR(j, n) cout << v1[i].query(j, j+1) << " ";
			cout << endl;
		}
	}
};

int main() {
	int n, k; read(n, k);
	HLD hld;
	hld.init(n, k);
	FOR(n-1) {
		int x, y; read(x, y);
		hld.ae(--x, --y);
	}
	hld.gen();
	hld.debug();
	print(hld.cnt);
}

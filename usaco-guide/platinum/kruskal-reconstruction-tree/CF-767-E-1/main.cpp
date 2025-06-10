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

template<bool imin>
struct ST {
	int n, h;
	vt<int> ms, v, d;
	ST(int n, span<int> a) : n(n), h(32-__builtin_clz(n)), ms(2*n), v(2*n, default_value()), d(n, -1) {
		FOR(n) ms[i+n]=a[i];
		FOR(i, n-1, 0, -1) ms[i]=combine(ms[i<<1], ms[i<<1|1]);
	}
	void apply(int i, int x) {
		v[i]=x ? ms[i] : default_value();
		if (i<n) d[i]=x;
	}
	void push(int i) {
		if (d[i]!=-1) {
			apply(i<<1, d[i]);
			apply(i<<1|1, d[i]);
			d[i]=-1;
		}
	}
	void propagate(int i) {
		FOR(j, h, 0, -1) {
			push(i>>j);
		}	
	}
	void build(int i) {
		for (; i>>=1; ) {
			if (d[i]!=-1) v[i]=d[i] ? ms[i] : default_value();
			else v[i]=combine(v[i<<1], v[i<<1|1]);
		}
	}
	void set(int l, int r, int x) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		propagate(l0), propagate(r0);
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) apply(l++, x);
			if (r&1) apply(--r, x);
		}
		build(l0), build(r0);
	}
	int query(int l, int r) {
		l+=n, r+=n;
		propagate(l), propagate(r-1);
		int ret=default_value();
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) ret=combine(ret, v[l++]);
			if (r&1) ret=combine(ret, v[--r]);
		}
		return ret;
	}
	int combine(int l, int r) {
		return imin ? min(l, r) : max(l, r);
	}
	int default_value() {
		return imin ? INT_MAX : INT_MIN;
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

struct KRT {
	int n, h;
	vt<int> dsu, w, depth, pos;
	vt<pii> tmp; RMQ<pii> rmq;
	vt<vt<int>> adj;
	KRT(int n) : n(n), h(n), dsu(2*n-1), adj(2*n-1), w(2*n-1, -1), depth(2*n-1), pos(2*n-1) {
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
		w[h]=i;
		h++;
	}
	void dfs(int v) {
		pos[v]=sz(tmp); tmp.eb(depth[v], v);
		EACH(u, adj[v]) {
			depth[u]=depth[v]+1;
			dfs(u);
			tmp.eb(depth[v], v);
		}
	}
	void gen() {
		dfs(2*n-2);
		rmq.init(tmp);
	}
	int pos_lca(int a, int b) {
		if (b<a) return -1;
		return rmq.query(a, b).s;
	}
	int danger(int u, ST<true>& minst, ST<false>& maxst) {
		int l=minst.query(0, n), r=maxst.query(0, n);
		l=pos_lca(l, pos[u]), r=pos_lca(pos[u], r);
		return max(l!=-1 ? w[l] : -1, r!=-1 ? w[r] : -1);
	}
};

struct edge {
	int u, v, w;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m; read(n, m);
	vt<edge> e(n-1);
	FOR(n-1) {
		int x, y, z; read(x, y, z);
		e[i]={--x, --y, z};
	}
	sort(all(e), [](const edge& a, const edge& b) { return a.w<b.w; });
	KRT krt(n);
	for (auto &[u, v, w] : e) krt.ae(u, v, w);
	krt.gen();
	ST<true> minst(n, span(krt.pos).subspan(0, n));
	ST<false> maxst(n, span(krt.pos).subspan(0, n));
	FOR(m) {
		int x, y; read(x);
		switch (x) {
			case 1:
				read(x, y); --x;
				minst.set(x, y, 1);
				maxst.set(x, y, 1);
				break;
			case 2:
				read(x, y); --x;
				minst.set(x, y, 0);
				maxst.set(x, y, 0);
				break;
			case 3:
				read(x);
				print(krt.danger(--x, minst, maxst));
				break;
		}
	}
}

/*
6 9
1 3 1
2 3 2
4 5 3
4 6 4
3 4 5
3 1
1 1 1
3 1
2 1 1
1 5 6
3 4
2 6 6
3 4
3 1
*/
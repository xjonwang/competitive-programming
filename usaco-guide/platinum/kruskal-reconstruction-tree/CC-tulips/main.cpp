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
	int n, h, timer;
	vt<int> dsu, w, tin, tout;
	vt<vt<int>> adj, up;
	KRT(int n) : n(n), h(n), timer(0), dsu(2*n-1), adj(2*n-1), w(2*n-1, 0), up(2*n-1, vt<int>(18, -1)), tin(2*n-1), tout(2*n-1) {
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
		up[u][0]=h, up[v][0]=h;
		w[h]=i;
		h++;
	}
	void dfs(int v) {
		tin[v]=timer++;
		EACH(u, adj[v]) dfs(u);
		tout[v]=timer;
	}
	void gen() {
		FOR(j, 1, 18) FOR(i, 2*n-1) up[i][j]=up[i][j-1]!=-1 ? up[up[i][j-1]][j-1] : -1; 
		dfs(2*n-2);
		oset<int> os;
		FOR(n) os.insert(tin[i]);
		FOR(2*n-1) tin[i]=os.order_of_key(tin[i]), tout[i]=os.order_of_key(tout[i]);
	}
	int trav(int u, int k) {
		FOR(i, 17, -1, -1) if (up[u][i]!=-1 && w[up[u][i]]<=k) u=up[u][i];
		return u;
	}
};

struct ST {
	int n, h;
	vt<int> mi, mif, d;
	ST(int n) : n(n), h(32-__builtin_clz(n)), mi(2*n, 0), mif(2*n, 0), d(n, 0) {
		FOR(i, n, 2*n) mif[i]=1;
		FOR(i, n-1, 0, -1) mif[i]=mif[i<<1]+mif[i<<1|1];
	}
	void apply(int i, int x) {
		mi[i]+=x;
		if (i<n) d[i]+=x;
	}
	void push(int i) {
		if (d[i]) {
			apply(i<<1, d[i]);
			apply(i<<1|1, d[i]);
			d[i]=0;
		}
	}
	void propagate(int i) {
		FOR(j, h, 0, -1) {
			push(i>>j);
		}
	}
	void build(int i) {
		for (; i>>=1; ) {
			mi[i]=min(mi[i<<1], mi[i<<1|1]);
			if (mi[i<<1]<mi[i<<1|1]) mif[i]=mif[i<<1];
			else if (mi[i<<1]>mi[i<<1|1]) mif[i]=mif[i<<1|1];
			else mif[i]=mif[i<<1]+mif[i<<1|1];
			if (d[i]) mi[i]+=d[i];
		}
	}
	void add(int l, int r, int x) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		propagate(l0), propagate(r0);
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) apply(l++, x);
			if (r&1) apply(--r, x);
		}
		build(l0), build(r0);
	}
	int value(int i) {
		return mi[i]==0 ? mif[i] : 0;
	}
	int query(int l, int r) {
		l+=n, r+=n;
		propagate(l), propagate(r-1);
		int ret=0;
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) ret+=value(l++);
			if (r&1) ret+=value(--r);
		}
		return ret;
	}
};

struct edge {
	int u, v, w;
};
struct query {
	int t, l, r;
};

void solve() {
	int n; read(n);
	vt<edge> e(n-1);
	FOR(n-1) {
		int x, y, z; read(x, y, z);
		e[i]={--x, --y, z};
	}
	sort(all(e), [](const edge& a, const edge& b) { return a.w<b.w; });
	KRT krt(n);
	for (auto &[u, v, w] : e) krt.ae(u, v, w);
	krt.gen();
	int m, k; read(m, k);
	ST st(n);
	queue<query> q;
	FOR(m) {
		int x, y, z; read(x, y, z);
		y=krt.trav(--y, z);
		while (sz(q) && q.front().t<=x) {
			auto [_, l, r]=q.front(); q.pop();
			st.add(l, r, -1);
		}
		print(st.query(krt.tin[y], krt.tout[y]));
		st.add(krt.tin[y], krt.tout[y], 1);
		q.push({x+k, krt.tin[y], krt.tout[y]});
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}

/*
1
5
1 2 1
4 5 2
1 5 3
2 3 4
6 10
1 2 4
10 4 4
20 1 0
21 2 1
22 5 2
23 4 4
*/
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

struct ST {
	int n;
	vt<int> ma, mai;
	ST(int n, const vt<int>& v) : n(n), ma(2*n), mai(2*n) {
		FOR(n) ma[i+n]=v[i], mai[i+n]=i;
		FOR(i, n-1, 0, -1) {
			ma[i]=max(ma[i<<1], ma[i<<1|1]);
			mai[i]=ma[i<<1]>ma[i<<1|1] ? mai[i<<1] : mai[i<<1|1];
		}
	}
	void set(int i, int x) {
		for (ma[i+=n]=x; i>>=1; ) {
			ma[i]=max(ma[i<<1], ma[i<<1|1]);
			mai[i]=ma[i<<1]>ma[i<<1|1] ? mai[i<<1] : mai[i<<1|1];
		}
	}
	pii query(int l, int r) {
		int val=-1, idx=-1;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) {
				if (umax(val, ma[l])) idx=mai[l];
				l++;
			}
			if (r&1) {
				--r;
				if (umax(val, ma[r])) idx=mai[r];
			}
		}
		return {val, idx};
	}
};

struct KRT {
	int n, h, timer;
	vt<int> dsu, tin, tout;
	vt<vt<int>> adj;
	vt<bool> vis;
	KRT(int n) : n(n), h(n), timer(0), dsu(2*n-1), adj(2*n-1), vis(2*n-1, 0), tin(2*n-1), tout(2*n-1) {
		iota(dsu.begin(), dsu.begin()+n, 0);
	}
	int get(int u) {
		return u==dsu[u] ? u : dsu[u]=get(dsu[u]);
	}
	void ae(int u, int v) {
		u=get(u), v=get(v);
		if (u==v) return;
		dsu[h]=h;
		dsu[u]=dsu[v]=h;
		adj[h].pb(u), adj[h].pb(v);
		h++;
	}
	void gen() {
		FOR(i, 2*n-2, -1, -1) if (!vis[i]) dfs(i);
	}
	void dfs(int v) {
		vis[v]=1;
		tin[v]=timer++;
		EACH(u, adj[v]) dfs(u);
		tout[v]=timer;
	}
};

struct edge {
	int u, v;
	bool del;	
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, q; read(n, m, q);
	vt<int> a(n); read(a);
	vt<edge> e(m);
	FOR(m) {
		int x, y; read(x, y);
		e[i]={--x, --y, 0};
	}
	vt<pii> v(q);
	FOR(q) {
		int x, y; read(x, y); --y;
		if (x==2) e[y].del=1;
		v[i]={x, y};
	}
	KRT krt(n);
	FOR(m) if (!e[i].del) krt.ae(e[i].u, e[i].v);
	vt<int> lca;
	reverse(all(v));
	for (auto &[c, x] : v) {
		switch (c) {
			case 1:
				lca.pb(krt.get(x));
				break;
			case 2:
				krt.ae(e[x].u, e[x].v);
				break;
		}
	}
	krt.gen();
	vt<int> pa(2*n-1, 0);
	FOR(n) pa[krt.tin[i]]=a[i];
	ST st(2*n-1, pa);
	vt<int> ans;
	reverse(all(lca));
	EACH(a, lca) {
		auto [val, idx]=st.query(krt.tin[a], krt.tout[a]);
		ans.pb(val);
		st.set(idx, 0);
	}
	EACH(a, ans) print(a);
}
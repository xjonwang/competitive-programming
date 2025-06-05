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

struct ST {
	int n;
	vt<int> v;
	ST(int n) : n(n), v(2*n, 1) {}
	void set(int l, int r) {
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) v[l++]=0;
			if (r&1) v[--r]=0;
		}
	}
	int query(int i) {
		for (i+=n; i>0; i>>=1) {
			if (v[i]==0) return 0;
		}
		return 1;
	}
};

#define MAX_N 100000

vt<vt<int>> adj;
int timer;
vt<int> tin, tout, d;
int up[MAX_N][17];

void dfs(int v, int p=-1) {
	tin[v]=timer++;
	up[v][0]=p;
	EACH(u, adj[v]) {
		if (u==p) continue;
		d[u]=d[v]+1;
		dfs(u, v);
	}
	tout[v]=timer;
}
int lift(int x, int k) {
	FOR(17) if (x!=-1 && k&(1<<i)) x=up[x][i];
	return x; 
}
int lca(int a, int b) {
	a=lift(a, d[a]-min(d[a], d[b]));
	b=lift(b, d[b]-min(d[a], d[b]));
	if (a==b) return a;
	FOR(i, 16, -1, -1) if (up[a][i]!=up[b][i]) a=up[a][i], b=up[b][i];
	return up[a][0];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("gathering.in", "r", stdin);
	freopen("gathering.out", "w", stdout);
	int n, m; read(n, m);
	adj.rsz(n), tin.rsz(n), tout.rsz(n), d.rsz(n);
	FOR(n-1) {
		int x, y; read(x, y); --x, --y;
		adj[x].pb(y), adj[y].pb(x);
	}
	d[0]=0;
	dfs(0);
	FOR(i, 1, 17) FOR(j, n) up[j][i]=up[j][i-1]!=-1 ? up[up[j][i-1]][i-1] : -1;
	ST st(n);
	vt<vt<int>> tadj(n);
	vt<int> in(n);
	FOR(m) {
		int x, y; read(x, y); --x, --y;
		tadj[x].pb(y), in[y]++;
		if (lca(x, y)==x) {
			x=lift(y, d[y]-d[x]-1);
			st.set(0, tin[x]), st.set(tout[x], n);
		} else {
			st.set(tin[x], tout[x]);
		}
	}
	queue<int> q;
	FOR(n) if (in[i]==0) q.push(i);
	int tcnt=0;
	while (sz(q)) {
		int v=q.front(); q.pop();
		tcnt++;
		EACH(u, tadj[v]) if (--in[u]==0) q.push(u);
	}
	if (tcnt<n) {
		FOR(n) print(0);
	} else {
		FOR(n) print(st.query(tin[i]));
	}
}
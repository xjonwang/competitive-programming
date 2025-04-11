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

vt<vt<int>> adj;
vt<bool> vis;
vt<int> od, cc;

void dfs1(int v) {
	vis[v]=1;
	EACH(u, adj[v]) if (!vis[u]) dfs1(u);
	od.pb(v);
}

void dfs2(int v, int id) {
	vis[v]=1;
	cc[v]=id;
	EACH(u, adj[v]) {
		if (!vis[u]) dfs2(u, id);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, k, x; read(n, m);
	vt<int> v(n); read(v);
	vt<int> s1(n, -1), s2(n, -1);
	adj.assign(2*m, vt<int>()), vis.assign(2*m, 0), cc.resize(2*m);
	FOR(m) {
		read(k);	
		FOR(j, k) {
			read(x); --x;
			if (s1[x]!=-1) s2[x]=i;
			else s1[x]=i;
		}
	}
	FOR(n) {
		int x1=s1[i]*2, x2=x1+1, y1=s2[i]*2, y2=y1+1;
		if (v[i]) {
			adj[x1].pb(y1);
			adj[x2].pb(y2);
			adj[y1].pb(x1);
			adj[y2].pb(x2);
		} else {
			adj[x1].pb(y2);
			adj[x2].pb(y1);
			adj[y1].pb(x2);
			adj[y2].pb(x1);
		}
	}
	FOR(2*m) if (!vis[i]) dfs1(i);
	vis.assign(2*n, 0);
	int id=0;
	reverse(all(od));
	EACH(i, od) if (!vis[i]) dfs2(i, id++);
	bool ans=1;
	FOR(i, 0, 2*m, 2) if (cc[i]==cc[i+1]) ans=0;
	print(ans ? "YES" : "NO");
}
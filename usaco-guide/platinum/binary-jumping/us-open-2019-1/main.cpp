#include "grader.h"
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

vt<vt<int>> adj, up;
vt<int> d, si;
vt<pii> off, coord;

template <typename T1, typename T2>
pair<T1, T2> operator+(const std::pair<T1, T2>& a, const std::pair<T1, T2>& b) {
    return {a.f+b.f, a.s+b.s};
}

void dfs1(int v, int p=-1) {
	up[v][0]=p;
	d[v]=p!=-1 ? d[p]+1 : 0;
	si[v]=1;
	EACH(u, adj[v]) {
		if (u!=p) {
			adj[u].erase(find(all(adj[u]), v));
			dfs(u, v);
			si[v]+=si[u];
		}
	}
}

void dfs2(int v) {
	int n=sz(adj[v]);
	vt<int> l(n+1), r(n+1);
	l[0]=0, r[n]=0;
	FOR(n) l[i+1]=l[i]+si[adj[v][i]];
	FOR(i, n-1, -1, -1) r[i]=r[i+1]+si[adj[v][i]];
	FOR(n) {
		int u=adj[v][i];
		off[u]={r[i+1], l[i]};
		dfs2(u);
	}
}

void dfs3(int v, int p=0) {
	coord[v]=coord[p]+off[v];
	EACH(u, adj[v]) dfs3(u, v);
}

int lift(int x, int k) {
	FOR(17) if (k&(1<<i)) x=up[x][i];
	return x;
}

int lca(int a, int b) {
	a=lift(a, d[a]-min(d[a], d[b]));
	b=lift(b, d[b]-min(d[a], d[b]));
	if (a==b) return a;
	FOR(i, 16, -1, -1) if (up[a][i]!=up[b][i]) a=up[a][i], b=up[b][i];
	return up[a][0];
}

void addRoad(int a, int b){
	adj.resize(getN());
	adj[a].pb(b), adj[b].pb(a);
}

void buildFarms(){
	int n=getN();
	up.assign(n, vt<int>(17, -1));
	d.resize(n), si.resize(n), off.resize(n), coord.resize(n);
	dfs1(0);
	off[0]={0, 0};
	dfs2(0);
	coord[0]={1, 1};
	dfs3(0);
	FOR(i, 1, 17) FOR(j, n) if (up[j][i-1]!=-1) up[j][i]=up[up[j][i-1]][i-1];
	FOR(n) setFarmLocation(i, coord[i].f, coord[i].s);
}

void notifyFJ(int a, int b){
	int u=lca(a, b);
	addBox(coord[u].f, coord[u].s, coord[a].f, coord[a].s);
	if (b!=u) {
		u=lift(b, d[b]-d[u]-1);
		addBox(coord[u].f, coord[u].s, coord[b].f, coord[b].s);
	}
}

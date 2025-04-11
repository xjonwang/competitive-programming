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

vt<vt<int>> adj, radj, sadj;
vt<bool> vis;
vt<int> od, cc, in;

void dfs1(int v) {
	vis[v]=1;
	EACH(u, adj[v]) if (!vis[u]) dfs1(u);
	od.pb(v);
}

void dfs2(int v, int id) {
	vis[v]=1;
	cc[v]=id;
	EACH(u, radj[v]) {
		if (!vis[u]) {
			dfs2(u, id);
		} else if (cc[u]!=id) {
			sadj[cc[u]].pb(id);
			in[id]++;
		}
	}
}

void solve() {
	int n, m, x, y; read(n, m);
	adj.assign(2*n, {}), radj.assign(2*n, {}), sadj.assign(2*n, {}), vis.assign(2*n, 0), cc.resize(2*n), in.assign(2*n, 0), od.clear();
	string qu; read(qu);
	FOR(m) {
		read(x, y);
		int x1=2*abs(x)-2, x2=x1+1, y1=2*abs(y)-2, y2=y1+1;
		adj[x<0 ? x1 : x2].pb(y>0 ? y1 : y2);
		adj[y<0 ? y1 : y2].pb(x>0 ? x1 : x2);
	}
	FOR(v, 2*n) EACH(u, adj[v]) radj[u].pb(v);
	FOR(2*n) if (!vis[i]) dfs1(i);
	reverse(all(od));
	vis.assign(2*n, 0);
	int id=0;
	EACH(v, od) if (!vis[v]) dfs2(v, id++); 
	bool ans=1;
	FOR(n) if (cc[i*2]==cc[i*2+1]) ans=0; 
	vt<bool> e(id, 0), dpe(id, 0);
	FOR(n) {
		int u1=i*2, u2=u1+1;
		if (qu[i]=='A') {
			dpe[cc[u1]]=e[cc[u1]]=1;
			dpe[cc[u2]]=e[cc[u2]]=1;
		} else {
		}
	}
	queue<int> q;
	FOR(id) if (in[i]==0) q.push(i);
	while (sz(q)) {
		int v=q.front(); q.pop();
		EACH(u, adj[v]) {
			if (e[u] && dpe[v]) ans=0;
			if (ma[u]<dpt[v])
			dpe[u]=dpe[v]|dpe[u];
			umin(dpt[u], dpt[v]);
			if (--in[u]==0) q.push(u);
		}
	}
	print(ans ? "TRUE" : "FALSE");
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}
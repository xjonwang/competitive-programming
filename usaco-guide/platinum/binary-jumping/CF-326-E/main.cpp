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

vt<vt<pair<int, vt<int>>>> up;
vt<vt<int>> adj;
vt<int> d;

void dfs(int v, int p=-1) {
	d[v]=p!=-1 ? d[p]+1 : 0;
	up[v][0].f=p;
	EACH(u, adj[v]) if (u!=p) dfs(u, v);
}

vt<int> merge(const vt<int> &a, const vt<int> &b) {
	int i=0, j=0;
	vt<int> ret;
	while (sz(ret)<10 && i<sz(a) && j<sz(b)) {
		if (a[i]<b[j]) ret.pb(a[i++]);
		else ret.pb(b[j++]);
	}
	while (sz(ret)<10 && i<sz(a)) ret.pb(a[i++]);
	while (sz(ret)<10 && j<sz(b)) ret.pb(b[j++]);
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, q, x, y; read(n, m, q);
	adj.resize(n), d.resize(n);
	up.assign(n, vt<pair<int, vt<int>>>(17, {-1, {}}));
	FOR(n-1) {
		read(x, y); --x, --y;
		adj[x].pb(y), adj[y].pb(x);
	}
	dfs(0);
	FOR(i, 1, m+1) {
		read(x); --x;
		if (sz(up[x][0].s)<10) up[x][0].s.pb(i);
	}
	FOR(i, 1, 17) {
		FOR(j, n) {
			if (up[j][i-1].f!=-1) {
				up[j][i]={up[up[j][i-1].f][i-1].f, merge(up[j][i-1].s, up[up[j][i-1].f][i-1].s)};
			}
		}
	}
	auto lift=[&](int x, int k) {
		FOR(17) if (k&(1<<i)) x=up[x][i].f;
		return x;
	};
	auto lca=[&](int a, int b) {
		a=lift(a, d[a]-min(d[a], d[b]));
		b=lift(b, d[b]-min(d[a], d[b]));
		if (a==b) return a;
		FOR(i, 16, -1, -1) if (up[a][i].f!=up[b][i].f) a=up[a][i].f, b=up[b][i].f;
		return up[a][0].f;
	};
	auto liftv=[&](int x, int k) {
		vt<int> ret;
		FOR(17) if (k&(1<<i)) ret=merge(ret, up[x][i].s), x=up[x][i].f;
		return ret;
	};
	FOR(q) {
		read(x, y); --x, --y;
		int a=lca(x, y);
		vt<int> ans;
		ans=merge(ans, liftv(x, d[x]-d[a]));
		ans=merge(ans, liftv(y, d[y]-d[a]));
		ans=merge(ans, up[a][0].s);
		read(x);
		write(min(x, sz(ans)), " ");
		FOR(j, min(x, sz(ans))) write(ans[j], " ");
		print();
	}
}

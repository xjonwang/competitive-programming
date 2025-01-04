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

#define int long long

vt<vt<pair<int, ll>>> up;
vt<pii> ed;
vt<vt<pii>> adj;
vt<bool> shop;
vt<int> d1;
vt<ll> d2, sub;

void dfs(int v, ll d, int p=-1) {
	up[v][0].f=p;
	d1[v]=p!=-1 ? d1[p]+1 : 0;
	d2[v]=d;
	if (shop[v]) sub[v]=d;
	for (auto &[u, w] : adj[v]) {
		if (u!=p) {
			dfs(u, d+w, v);
			umin(sub[v], sub[u]);
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, q, e, x, y, z; read(n, m, q, e);
	up.assign(n, vt<pair<int, ll>>(17, {-1, 1e18}));
	ed.resize(n-1), adj.resize(n), shop.assign(n, 0), d1.resize(n), d2.resize(n), sub.assign(n, 1e18);
	FOR(n-1) {
		read(x, y, z);
		ed[i]={--x, --y};
		adj[x].pb({y, z}), adj[y].pb({x, z});
	}
	FOR(m) {
		read(x);
		shop[--x]=1;
	}
	dfs(--e, 0);
	FOR(n) up[i][0].s=sub[i]-2*d2[i];
	FOR(i, 1, 17) FOR(j, n) if (up[j][i-1].f!=-1) up[j][i]={up[up[j][i-1].f][i-1].f, min(up[j][i-1].s, up[up[j][i-1].f][i-1].s)};
	auto lift=[&](int x, int k) {
		FOR(17) if (k&(1<<i)) x=up[x][i].f;	
		return x;
	};
	auto liftv=[&](int x, int k) {
		ll ret=1e18;
		FOR(17) {
			if (k&(1<<i)) {
				umin(ret, up[x][i].s);
				x=up[x][i].f;
			}
		}
		return ret;
	};
	FOR(q) {
		read(x, y); --x, --y;
		auto [a, b]=ed[x];
		if (d1[a]<=d1[y] && a==lift(y, d1[y]-d1[a]) && d1[b]<=d1[y] && b==lift(y, d1[y]-d1[b])) {
			ll ans=liftv(y, d1[y]-min(d1[a], d1[b]))+d2[y];
			if (ans<1e17) print(ans);
			else print("oo");
		} else {
			print("escaped");
		}
	}
}

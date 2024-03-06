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

int n, m, w, x, y, z;
vt<vt<pii>> adj;

struct node {
	ll w, d;
	int v;
};

struct cmp {
	bool operator()(const node& a, const node& b) {
		return a.w!=b.w ? a.w>b.w : a.d>b.d;
	}
};

vt<pll> dijkstra(int st, vt<ll>& o) {
	priority_queue<node, vt<node>, cmp> pq;
	vt<pll> dist(n, {LLONG_MAX, LLONG_MAX});
	dist[st]={0, o[st]}; pq.push({0, o[st], st});
	while (sz(pq)) {
		auto [w, d, v]=pq.top(); pq.pop();
		if (w>dist[v].f || d>dist[v].s) continue;
		for (auto [u, c] : adj[v]) {
			if (umin(dist[u].f, w+c)) dist[u].s=min(d, o[u]), pq.push({w+c, min(d, o[u]), u});
			else if (dist[u].f==w+c && umin(dist[u].s, d)) pq.push({w+c, min(d, o[u]), u});
		}
	}
	return dist;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, m, w, x, y, z); --w, --x, --y, --z;
	adj.resize(n);
	int a, b, c;
	FOR(m) {
		read(a, b, c); --a, --b;
		adj[a].pb({b, c});
		adj[b].pb({a, c});
	}
	vt<ll> ud(n, LLONG_MAX), vd(n, LLONG_MAX);
	priority_queue<pll, vt<pll>, greater<pll>> pq;
	ud[y]=0; pq.push({0, y});
	while (sz(pq)) {
		auto [w, v]=pq.top(); pq.pop();
		if (w>ud[v]) continue;
		for (auto [u, c] : adj[v]) if (umin(ud[u], w+c)) pq.push({w+c, u});
	}
	vd[z]=0; pq.push({0, z});
	while (sz(pq)) {
		auto [w, v]=pq.top(); pq.pop();
		if (w>vd[v]) continue;
		for (auto [u, c] : adj[v]) if (umin(vd[u], w+c)) pq.push({w+c, u});
	}
	vt<pll> su=dijkstra(w, ud), sv=dijkstra(w, vd), tu=dijkstra(x, ud), tv=dijkstra(x, vd);
	ll md=su[x].f;
	ll ans=ud[z];
	FOR(n) {
		if (su[i].f+tv[i].f==md) umin(ans, su[i].s+tv[i].s);
		if (sv[i].f+tu[i].f==md) umin(ans, sv[i].s+tu[i].s);
	}
	print(ans);
}
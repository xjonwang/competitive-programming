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

#define MX 10000001
#define AL 2

ll n, k;
vt<ll> xo;
vt<vt<pair<int, ll>>> adj;

void dfs(int v, ll x) {
	xo[v]=x;
	for (auto &[u, w] : adj[v]) dfs(u, x^w);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, k);
	adj.resize(n), xo.resize(n);
	int x; ll y;
	FOR(i, 1, n) {
		read(x, y);
		adj[--x].pb({i, y});
	}
	dfs(0, 0);
	sort(all(xo));
	ll ra=n*n, ans=0;
	vt<pii> prev={{0, 0}}, next;
	vt<int> pidx(n, 0), nidx(n);
	vt<ar<ll, 2>> cnt(n), tr(n);
	FOR(i, 61, -1, -1) {
		ll sc=0; int t=0;
		cnt.assign(n, ar<ll, 2>{0, 0});
		tr.assign(n, ar<ll, 2>{-1, -1});
		nidx[0]=t;
		FOR(j, 1, n) nidx[j]=(pidx[j]!=pidx[j-1] || (xo[j]^xo[j-1])&(1ll<<i)) ? ++t : t;
		FOR(j, n) tr[pidx[j]][(xo[j]>>i)&1]=nidx[j];
		FOR(j, n) cnt[pidx[j]][(xo[j]>>i)&1]++;
		for (auto &[u, v] : prev) {
			sc+=cnt[u][0]*cnt[v][1];
			sc+=cnt[u][1]*cnt[v][0];
		}
		if (ra-sc>=k) {
			ra-=sc;
			for (auto &[u, v] : prev) {
				if (tr[u][0]!=-1 && tr[v][0]!=-1) next.pb({tr[u][0], tr[v][0]});
				if (tr[u][1]!=-1 && tr[v][1]!=-1) next.pb({tr[u][1], tr[v][1]});
			}
		} else {
			ans+=(1ll<<i);
			for (auto &[u, v] : prev) {
				if (tr[u][0]!=-1 && tr[v][1]!=-1) next.pb({tr[u][0], tr[v][1]});
				if (tr[u][1]!=-1 && tr[v][0]!=-1) next.pb({tr[u][1], tr[v][0]});
			}
		}
		swap(prev, next);
		swap(pidx, nidx);
		next.clear();
	}
	print(ans);
}
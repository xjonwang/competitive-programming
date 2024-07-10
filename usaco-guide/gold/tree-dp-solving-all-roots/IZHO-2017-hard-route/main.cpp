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

int n;
ll ans=0, acnt=2;
vt<vt<int>> adj;
vt<pii> h, par;

void dfs(int v, int p=-1) {
	EACH(u, adj[v]) {
		if (u==p) continue;
		dfs(u, v);
		if (umax(h[v].f, h[u].f+1)) h[v].s=h[u].s;
		else if (h[v].f==h[u].f+1) h[v].s+=h[u].s;
	}
}

void dfs2(int v, int p=-1) {
	map<int, int> cnt;
	multiset<int> ad;
	EACH(u, adj[v]) if (u!=p) cnt[h[u].f+1]+=h[u].s, ad.insert(h[u].f+1);
	ll l1=0, l2=0, c1=0, c2=0;
	if (par[v].f && sz(ad)>=2) {
		l1=*ad.rbegin(), c1=cnt[l1];
		l2=*next(ad.rbegin()), c2=cnt[l2];
		ll hard=(par[v].f+l2)*l1;
		if (umax(ans, hard)) acnt=par[v].s*c2;
		else if (ans==hard) acnt+=par[v].s*c2;
	}
	if (par[v].f) {
		ad.insert(par[v].f);
		cnt[par[v].f]+=par[v].s;
	}
	EACH(u, adj[v]) {
		if (u==p) continue;
		int t=h[u].f+1;
		ad.erase(ad.find(t));
		cnt[t]-=h[u].s;
		if (cnt[t]==0) cnt.erase(t);
		if (sz(ad)>=2) {
			l1=l2=c1=c2=0;
			l1=*ad.rbegin(), c1=cnt[l1];
			l2=*next(ad.rbegin()), c2=cnt[l2];
			ll hard=(t+l2)*l1;
			if (umax(ans, hard)) acnt=h[u].s*c2;
			else if (ans==hard) acnt+=h[u].s*c2;
		}
		ad.insert(t);
		cnt[t]+=h[u].s;
	}
	if (!par[v].f) {
		ad.insert(par[v].f);
		cnt[par[v].f]+=par[v].s;
	}
	EACH(u, adj[v]) {
		if (u==p) continue;
		cnt[h[u].f+1]-=h[u].s;
		if (cnt[h[u].f+1]==0) cnt.erase(h[u].f+1);
		par[u]={cnt.rbegin()->f+1, cnt.rbegin()->s};
		dfs2(u, v);
		cnt[h[u].f+1]+=h[u].s;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n);
	adj.resize(n), par.resize(n), h.assign(n, {0, 1});
	int x, y;
	FOR(n-1) {
		read(x, y); --x, --y;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	dfs(0);
	par[0]={0, 1};
	dfs2(0);
	print(ans, acnt/2);
}
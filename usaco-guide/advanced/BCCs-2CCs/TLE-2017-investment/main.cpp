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

struct com {
	int x, y, v;
};

struct cmp {
	bool operator()(const com &a, const com& b) const {
		return a.v<b.v;
	}
};

#define MX 100001

int n, m, k1, k2;
vt<vt<int>> adj;
bool vis[MX];
int va[MX], ti[MX], t, lo[MX], st, cc[MX];
ll a[MX];
set<com, cmp> val;
map<pii, int> mp; 

void dfs(int v, int p=-1) {
	vis[v]=1;
	EACH(u, adj[v]) {
		if (u==p) continue;
		if (!vis[u]) {
			if (v==0) st++;
			dfs(u, v);
			umin(lo[v], lo[u]);
			if (lo[u]>=ti[v]) cc[u]=1;
		} else {
			umin(lo[v], ti[u]);
		}
	}
}

void dfs2(int v, int idx) {
	vis[v]=1;
	if (cc[v]==0) cc[v]=idx;
	a[cc[v]]+=va[v];
	FOR(u, adj[v]) {
		if (!vis[u]) {
			int cu=cc[u], cv=cc[v];
			dfs(u, cv);
			if (cv!=cu) {
				if (cv>cu) swap(cv, cu);
				int sum=va[u]+va[v];
				pii tp={cv, cu};
				if (mp.find(tp)) {
					if (sum>mp[tp]) {
						val.erase({cv, cu, mp[tp]});
						mp[tp]=sum;
						val.insert({cv, cu, sum});
					}	
				} else {
					if (sz(val)<k2) {
						val.insert({cv, cu, sum});
						mp[tp]=sum;
					} else {
						if (sum>val.begin()->v) {
							
						}
					}
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, m, k1, k2);
	adj.resize(n);
	int x, y;
	FOR(m) {
		read(x, y); --x, --y;
		adj[x].pb(y), adj[y].pb(x);
	}
	FOR(n) read(va[i]);
	dfs(0);
	int idx=1;
	FOR(i, 1, n) if (cc[i]) cc[i]=idx++;
	dfs2(0);

}
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

struct ST {
	int n; vt<int> v;
	void init(int a) {
		n=a;
		v=vt<int>(2*n, INT_MAX);	
	}
	void set(int i, int x) {
		for (v[i+=n]=x; i>>=1; ) v[i]=min(v[i<<1], v[i<<1|1]);
	}
	int query(int l, int r) {
		int ret=INT_MAX;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) umin(ret, v[l++]);
			if (r&1) umin(ret, v[--r]);
		}
		return ret;
	}
};

int n, m;
vt<vt<int>> adj;
vt<int> ti, lo, cc;
vt<bool> vis, inst;
set<int> viss;
ST tis;
int t, ccid;
stack<int> st;

void dfs(int v, int x) {
	vis[v]=1;
	ti[v]=lo[v]=t++;
	st.push(v);
	inst[v]=1;
	if (v&1) {
		viss.erase(v/2);
		tis.set(v/2, ti[v]);
		EACH(u, adj[v]) {
			if (!vis[u]) {
				dfs(u, x);
				umin(lo[v], lo[u]);
			} else if (inst[u]) {
				umin(lo[v], ti[u]);
			}
		}
	} else {
		int l=max(v/2-x, 0), r=min(v/2+x, n-1);
		umin(lo[v], tis.query(l, v/2));
		umin(lo[v], tis.query(v/2+1, r+1));
		for (auto it=viss.lower_bound(l); it!=viss.end() && *it<v/2; it=viss.lower_bound(l)) {
			int u=*it*2+1;
			assert(!vis[u]);
			dfs(u, x);
			umin(lo[v], lo[u]);
		}
		for (auto it=viss.upper_bound(v/2); it!=viss.end() && *it<=r; it=viss.upper_bound(v/2)) {
			int u=*it*2+1;
			assert(!vis[u]);
			dfs(u, x);
			umin(lo[v], lo[u]);
		}
	}
	if (lo[v]==ti[v]) {
		int u;
		do {
			u=st.top(); st.pop();
			inst[u]=0;
			cc[u]=ccid;
			if (u&1) tis.set(u/2, INT_MAX);
		} while (u!=v);
		ccid++;
	}
}

bool check(ll x) {
	vis.assign(2*n, 0), inst.assign(2*n, 0);
	tis.init(n);
	FOR(n) viss.insert(i);
	t=ccid=0;
	FOR(2*n) {
		if (!vis[i]){
			dfs(i, x-1);
		}
	}
	assert(sz(st)==0);
	FOR(n) if (cc[2*i]==cc[2*i+1]) return false;
	return true;
}

void solve() {
	int x, y; read(n, m);
	adj.assign(2*n, {}), ti.resize(2*n), lo.resize(2*n), cc.resize(2*n);
	FOR(m) {
		read(x, y); --x, --y;
		int x1=2*x, x2=x1+1, y1=2*y, y2=y1+1;
		adj[x2].pb(y1);
		adj[y2].pb(x1);
	}
	FOR(2*n) sort(all(adj[i])), adj[i].erase(unique(all(adj[i])), adj[i].end());
	int ans=LASTTRUE(check, 1, n);
	print(ans);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}
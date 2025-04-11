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

using T=pair<pii, int>;

struct ST {
	int n; vt<pii> v;
	ST(int n) : n(n), v(2*n, {INT_MAX, -1}) {};
	void modify(int i, pii x) {
		for (v[i+=n]=x; i>>=1; ) {
			v[i]=min(v[i<<1], v[i<<1|1]);
		}
	}
	pii query(int l, int r) {
		pii ret={INT_MAX, -1};
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) umin(ret, v[l++]);
			if (r&1) umin(ret, v[--r]);
		}
		return ret;
	}	
};

vt<vt<int>> adj, radj, sadj;
vt<int> od, cc, in;
vt<bool> vis;

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
	int n, k, m, x, y; read(n, k, m);
	adj.assign(2*m, {}), radj.assign(2*m, {}), sadj.assign(2*m, {}), vis.assign(2*m, 0), od.clear(), cc.resize(2*m), in.assign(2*m, 0);
	vt<vt<pii>> v1(n), v2(n);
	FOR(m) {
		read(x, y); --x, --y;
		v1[x].pb({y, i});
		v2[y].pb({x, i});
	}
	FOR(n) sort(all(v1[i])), sort(all(v2[i]));
	FOR(n) {
		FOR(j, 1, sz(v1[i])) {
			auto [c1, i1]=v1[i][j];
			auto [c2, i2]=v1[i][j-1];
			int x1=i1*2, x2=x1+1, y1=i2*2, y2=y1+1;
			if (c1-c2<=k) {
				adj[x1].pb(x2);
				adj[y1].pb(y2);
			} else if (c1-c2<=2*k) {
				adj[x1].pb(y2);
				adj[y1].pb(x2);
			}
		}
		FOR(j, 1, sz(v2[i])) {
			auto [c1, i1]=v2[i][j];
			auto [c2, i2]=v2[i][j-1];
			int x1=i1*2, x2=x1+1, y1=i2*2, y2=y1+1;
			if (c1-c2<=k) {
				adj[x2].pb(x1);
				adj[y2].pb(y1);
			} else if (c1-c2<=2*k) {
				adj[x2].pb(y1);
				adj[y2].pb(x1);
			}
		}
	}
	vt<int> idx(n, 0);
	auto cmp=[](const T& a, const T& b) { return a.f.f > b.f.f; };
	priority_queue<T, vt<T>, decltype(cmp)> q(cmp);
	ST st(n);
	FOR(n) if (sz(v1[i])) st.modify(i, v1[i][0]), q.push({v1[i][0], i}), idx[i]++;
	while (sz(q)) {
		auto [p, r]=q.top(); q.pop();
		auto [c, id]=p;
		if (idx[r]<sz(v1[r])) {
			q.push({v1[r][idx[r]], r});
			st.modify(r, v1[r][idx[r]]);
			idx[r]++;
		} else {
			st.modify(r, {INT_MAX, -1});
		}
		auto [valr, ur]=st.query(r, min(n, r+k+1));
		int x1=2*id, x2=x1+1;
		if (valr-c<=k) {
			int y1=ur*2, y2=y1+1;
			adj[x1].pb(y1);
			adj[y1].pb(x1);
			adj[x2].pb(y2);
			adj[y2].pb(x2);
		}
		auto [vall, ul]=st.query(max(0, r-k), r+1);
		if (vall-c<=k) {
			int y1=ul*2, y2=y1+1;
			adj[x1].pb(y1);
			adj[y1].pb(x1);
			adj[x2].pb(y2);
			adj[y2].pb(x2);
		}
	}
	FOR(v, 2*m) EACH(u, adj[v]) radj[u].pb(v);
	swap(adj, radj);
	FOR(2*m) if (!vis[i]) dfs1(i);
	vis.assign(2*m, 0);
	reverse(all(od));
	int id=0, t=0;
	EACH(v, od) if (!vis[v]) dfs2(v, id++);
	bool valid=1;
	FOR(m) if (cc[2*i]==cc[2*i+1]) valid=0;
	if (valid) {
		queue<int> q;
		vt<int> ti(2*m);
		FOR(2*m) if (in[i]==0) q.push(i);
		while (sz(q)) {
			int v=q.front(); q.pop();
			ti[v]=t++;
			EACH(u, sadj[v]) if (--in[u]==0) q.push(u);
		}
		vt<int> ans(m);
		FOR(m) ans[i]=ti[cc[2*i]]>ti[cc[2*i+1]];
		print("Yes");
		print(ans);
	} else {
		print("No");
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}
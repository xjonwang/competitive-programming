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

struct pd {
	int sum, maxin, minin, maxpre, minpre, maxpost, minpost;
};

pd merge(const pd &l, const pd &r) {
	return {
		l.sum+r.sum,
		max(max(l.maxin, r.maxin), l.maxpost+r.maxpre),
		min(min(l.minin, r.minin), l.minpost+r.minpre),
		max(l.maxpre, l.sum+r.maxpre),
		min(l.minpre, l.sum+r.minpre),
		max(r.maxpost, r.sum+l.maxpost),
		min(r.minpost, r.sum+l.minpost)
	};
}

void solve() {
	int n; read(n);
	vt<vt<int>> up(n+1, vt<int>(18, -1));
	vt<vt<pd>> trav(n+1, vt<pd>(18));
	vt<vt<int>> adj(n+1);
	vt<int> val(n+1), d(n+1); val[0]=1;
	vt<pair<pii, int>> q;
	char c;
	int idx=1, x, y, z;
	FOR(n) {
		read(c);
		switch (c) {
		case '+':
			read(x, y);
			val[idx]=y;
			adj[--x].pb(idx);
			idx++;
			break;
		case '?':
			read(x, y, z);
			q.pb({{--x, --y}, z});
			break;
		}
	}
	function<void(int, int)> dfs=[&](int v, int p) {
		up[v][0]=p;
		d[v]=p!=-1 ? d[p]+1 : 0;
		EACH(u, adj[v]) if (u!=p) dfs(u, v);
	};
	dfs(0, -1);
	FOR(idx) trav[i][0]={val[i], max(val[i], 0), min(val[i], 0), max(val[i], 0), min(val[i], 0), max(val[i], 0), min(val[i], 0)};
	FOR(i, 1, 18) FOR(j, n) if (up[j][i-1]!=-1) up[j][i]=up[up[j][i-1]][i-1], trav[j][i]=merge(trav[j][i-1], trav[up[j][i-1]][i-1]);
	auto lift=[&](int x, int k) {
		FOR(18) if (k&(1<<i)) x=up[x][i];
		return x;
	};
	auto liftv=[&](int x, int k) {
		pd ret{};
		FOR(18) if (k&(1<<i)) ret=merge(ret, trav[x][i]), x=up[x][i];
		return ret;
	};
	auto lca=[&](int a, int b) {
		a=lift(a, d[a]-min(d[a], d[b]));
		b=lift(b, d[b]-min(d[a], d[b]));
		if (a==b) return a;
		FOR(i, 17, -1, -1) if (up[a][i]!=up[b][i]) a=up[a][i], b=up[b][i];
		return up[a][0];
	};
	FOR(sz(q)) {
		auto [a, b]=q[i].f;
		int t=q[i].s;
		int u=lca(a, b);
		pd l=liftv(a, d[a]-d[u]);
		pd r=liftv(b, d[b]-d[u]);
		swap(r.maxpre, r.maxpost);
		swap(r.minpre, r.minpost);
		pd ans=merge(merge(l, trav[u][0]), r);
		if (t>0) print(ans.maxin>=t ? "yes" : "no");
		else if (t<0) print(ans.minin<=t ? "yes" : "no");
		else print("yes");
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}

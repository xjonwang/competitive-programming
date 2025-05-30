#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define ar array
#define str string

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define vt vector
#define pb push_back
#define eb emplace_back
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

#define AL 26

template<typename T>
struct RMQ {
	int level(int x) { return 31-__builtin_clz(x); }
	vt<T> v; vt<vt<int>> jmp;
	int cmb(int a, int b) {
		return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); }
	void init(vt<T>&& _v) {
		v=move(_v); jmp={vt<int>(sz(v))};
		iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= sz(v); ++j) {
			jmp.pb(vt<int>(sz(v)-(1<<j)+1));
			FOR(i,sz(jmp[j])) jmp[j][i] = cmb(jmp[j-1][i],
				jmp[j-1][i+(1<<(j-1))]);
		}
	}
	int index(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return cmb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
	T query(int l, int r) { return v[index(l,r)]; }
};

struct LCA {
	int N; vt<vt<pii>> adj;
	vt<int> pos;
	vt<ll> d;
	vt<pll> tmp; RMQ<pll> r;
	void init(int _N) { N = _N; adj.resize(N); 
		pos=vt<int>(N); d=vt<ll>(N); }
	void ae(int x, int y, int z) { adj[x].pb({y, z}), adj[y].pb({x, z}); }
	void dfs(int x) {
		stack<pair<int, bool>> st;
		st.push({x, false});
		while (sz(st)) {
			auto [x, vis]=st.top(); st.pop();
			if (vis) {
				tmp.eb(d[x], x);
				continue;
			}
			pos[x]=sz(tmp);
			tmp.eb(d[x], x);
			for (auto &[y, w] : adj[x]) {
				d[y]=d[x]+w;
				adj[y].erase(find(all(adj[y]), make_pair(x, w)));
				st.push({x, true});
				st.push({y, false});
			}
		}
	}
	void gen(int R = 0) { d[R]=0; dfs(R); r.init(move(tmp)); }
	int lca(int u, int v){
		u = pos[u], v = pos[v]; if (u > v) swap(u,v);
		return r.query(u,v).s; }
	ll dist(int u, int v) {
		return d[u]+d[v]-2*d[lca(u,v)]; }
};

int n, idx;
LCA lca;
vt<char> v1;
vt<int> v2;
vt<ll> cnt;
vt<pair<ll, int>> mx;

void dfs1(int v) {
	if (v1[v]==idx) cnt[v]=v2[v];
	else cnt[v]=0;
	mx[v]={-1, -1};
	FOR(sz(lca.adj[v])) {
		auto [u, _]=lca.adj[v][i];
		dfs1(u);
		cnt[v]+=cnt[u];
		if (umax(mx[v].f, cnt[u])) mx[v].s=i;
	}
}

void dfs2(int v, ll &cost, ll p=0) {
	ll diff=2*mx[v].f-(p+cnt[v]);
	if (diff>0) {
		auto [u, w]=lca.adj[v][mx[v].s];
		cost-=diff*w;
		p+=cnt[v]-mx[v].f;
		dfs2(u, cost, p);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n);
	v1.resize(n), v2.resize(n); read(v1, v2);
	EACH(x, v1) x-='a';
	cnt.resize(n), mx.resize(n);
	lca.init(n);
	int x, y, z;
	FOR(n-1) {
		read(x, y, z);
		lca.ae(--x, --y, z);
	}
	vt<vt<int>> fl(AL);
	vt<ll> ans(AL);
	FOR(n) fl[v1[i]].pb(i);
	if (n>=1e5) return 0;
	lca.gen();
	FOR(AL) {
		if (sz(fl[i])<2) {
			ans[i]=0;
		} else {
			idx=i;
			int a=fl[i][0];
			FOR(j, 1, sz(fl[i])) a=lca.lca(a, fl[i][j]);
			ll cost=0;
			FOR(j, sz(fl[i])) cost+=v2[fl[i][j]]*(lca.dist(fl[i][j], a));
			dfs1(0);
			dfs2(a, cost);
			ans[i]=cost;
		}
	}	
	print(ans);
}
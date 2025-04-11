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

template<typename T>
struct RMQ {
	int level(int x) { return 31-__builtin_clz(x); }
	vt<T> v; vt<vt<int>> jmp;
	int cmb(int a, int b) {
		return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); }
	void init(const vt<T>& _v) {
		v = _v; jmp = {vt<int>(sz(v))};
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
	int N; vt<vt<int>> adj;
	vt<int> depth, pos, par, rev;
	vt<pii> tmp; RMQ<pii> r;
	void init(int _N) { N = _N; adj.resize(N); 
		depth = pos = par = rev = vt<int>(N); }
	void ae(int x, int y) { adj[x].pb(y), adj[y].pb(x); }
	void dfs(int x) {
		pos[x] = sz(tmp); tmp.eb(depth[x],x); 
		EACH(y,adj[x]) if (y != par[x]) {
			depth[y] = depth[par[y]=x]+1, dfs(y);
			tmp.eb(depth[x],x); }
	}
	void gen(int R = 0) { par[R] = R; dfs(R); r.init(tmp); }
	int lca(int u, int v){
		u = pos[u], v = pos[v]; if (u > v) swap(u,v);
		return r.query(u,v).s; }
	int dist(int u, int v) {
		return depth[u]+depth[v]-2*depth[lca(u,v)]; }
	vt<pii> compress(vt<int> S) {
		auto cmp = [&](int a, int b) { return pos[a] < pos[b]; };
		sort(all(S),cmp); FOR(i,sz(S)-1,-1,-1) S.pb(lca(S[i],S[i+1]));
		sort(all(S),cmp); S.erase(unique(all(S)),end(S));
		vt<pii> ret{{0,S[0]}}; FOR(i,sz(S)) rev[S[i]] = i;
		FOR(i,1,sz(S)) ret.eb(rev[lca(S[i-1],S[i])],S[i]);
		return ret;
	}
};

ll inv(ll a, ll b) {
	return 1<a ? b-inv(b%a, a)*b/a : 1;
}

#define MOD 1000000007
#define ERR -69

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 
using H = ar<int,2>;
H makeH(char c) { return {c,c}; }
uniform_int_distribution<int> BDIST(0.1*MOD,0.9*MOD);
const H base{BDIST(rng),BDIST(rng)};
const H ibase{(int)inv(base[0], MOD), (int)inv(base[1], MOD)};
H operator+(H l, H r) { 
	FOR(2) if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
	return l; }
H operator-(H l, H r) { 
	FOR(2) if ((l[i] -= r[i]) < 0) l[i] += MOD;
	return l; }
H operator*(H l, H r) { 
	FOR(2) l[i] = (ll)l[i]*r[i]%MOD;
	return l; }
vt<H> pows, powsi, up, down;

int n, c, r;
string str;
vt<vt<int>> adj, cadj, nodes;
vt<bool> vis;
vt<int> dsz, d, nd;
vt<pair<int, H>> sum;
LCA lca;

H dist(int a, int b) {
	int c=lca.lca(a, b);
	int ca=d[a]-d[c];
	H d1=down[a]-down[c]*pows[ca];
	H d2=(up[b]-up[c])*pows[ca]*powsi[d[c]];
	H dc=makeH(str[c])*pows[ca];
	return d1+dc+d2;
}

int dfsz(int v, int p=-1) {
	dsz[v]=1;
	EACH(u, adj[v]) {
		if (!vis[u] && u!=p) {
			dsz[v]+=dfsz(u, v);
		}
	}
	return dsz[v];
}

int dfsc(int v, int tsz, int p=-1) {
	EACH(u, adj[v]) {
		if (!vis[u] && u!=p && dsz[u]>tsz/2) {
			return dfsc(u, tsz, v);
		}
	}
	return v;
}

int centroid(int v=0, int p=-1) {
	int c=dfsc(v, dfsz(v), p);
	vis[c]=1;

	if (p!=-1) cadj[p].pb(c);

	EACH(u, adj[c]) {
		if (!vis[u]) {
			centroid(u, c);
		}
	}
	return c;
}

void dfsog(int v, int p=-1) {
	EACH(u, adj[v]) {
		if (u!=p) {
			d[u]=d[v]+1;
			down[u]=down[v]*base+makeH(str[u]);
			up[u]=up[v]+pows[d[u]]*makeH(str[u]);
			dfsog(u, v);
		}
	}
}

struct chash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(const H& x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		uint64_t h = 0;
		h ^= splitmix64(x[0] + FIXED_RANDOM);
		h ^= splitmix64(x[1] + FIXED_RANDOM + 101);
		return h;
	}
};

void dfs(int v) {
	nodes[v].pb(v);
	EACH(u, cadj[v]) {
		dfs(u);
		nodes[v].insert(nodes[v].end(), all(nodes[u]));
	}
}

void dfso2(int v, int d, int p=-1) {
	nd[d]=v;
	if (d>2*c) {
		sum[v]={ERR, {ERR, ERR}};
	} else if(d>=c) {
		int t=2*(d-c);
		if (t<=d && dist(nd[t], r)==dist(r, nd[t])) sum[v]={t, dist(nd[t], v)};
		else sum[v]={ERR, {ERR, ERR}};
	} else {
		sum[v]={-1, dist(r, v)};
	}
	EACH(u, adj[v]) {
		if (!vis[u] && u!=p) {
			dfso2(u, d+1, v);
		}
	}
}

bool dfso(int v) {
	vis[v]=1;
	EACH(u, cadj[v]) {
		if (dfso(u)) return true;
	}
	r=v;
	dfso2(v, 0);
	unordered_set<H, chash> e1;
	e1.insert(makeH(str[v]));
	EACH(u, cadj[v]) {
		EACH(x, nodes[u]) {
			if (sum[x].f==ERR) continue;
			if (sum[x].f>=0 && e1.count(sum[x].s)) return true; 
		}
		EACH(x, nodes[u]) {
			if (sum[x].f==ERR) continue;
			if (sum[x].f<=0) e1.insert(sum[x].s);
		}
	}
	unordered_set<H, chash> e2;
	reverse(all(cadj[v]));
	EACH(u, cadj[v]) {
		EACH(x, nodes[u]) {
			if (sum[x].f==ERR) continue;
			if (sum[x].f>=0 && e2.count(sum[x].s)) return true; 
		}
		EACH(x, nodes[u]) {
			if (sum[x].f==ERR) continue;
			if (sum[x].f<=0) e2.insert(sum[x].s);
		}
	}
	vis[v]=0;
	return false;
}

void dfse2(int v, int d, int p=-1) {
	nd[d]=v;
	if (d>2*c+1) {
		sum[v]={ERR, {ERR, ERR}};
	} else if (d>c) {
		int t=2*(d-c)-1;
		if (t<=d && dist(nd[t], r)==dist(r, nd[t])) sum[v]={t, dist(nd[t], v)};
		else sum[v]={ERR, {ERR, ERR}};
	} else {
		sum[v]={-1, dist(r, v)};
	}
	EACH(u, adj[v]) {
		if (!vis[u] && u!=p) {
			dfse2(u, d+1, v);
		}
	}
}

bool dfse(int v) {
	vis[v]=1;
	EACH(u, cadj[v]) {
		if (dfse(u)) return true;
	}
	r=v;
	dfse2(v, 0);
	unordered_set<H, chash> e1;
	e1.insert(makeH(str[v]));
	EACH(u, cadj[v]) {
		EACH(x, nodes[u]) {
			if (sum[x].f==ERR) continue;
			if (sum[x].f>=0 && e1.count(sum[x].s)) return true; 
		}
		EACH(x, nodes[u]) {
			if (sum[x].f==ERR) continue;
			if (sum[x].f<=0) e1.insert(sum[x].s);
		}
	}
	unordered_set<H, chash> e2;
	reverse(all(cadj[v]));
	EACH(u, cadj[v]) {
		EACH(x, nodes[u]) {
			if (sum[x].f==ERR) continue;
			if (sum[x].f>=0 && e2.count(sum[x].s)) return true; 
		}
		EACH(x, nodes[u]) {
			if (sum[x].f==ERR) continue;
			if (sum[x].f<=0) e2.insert(sum[x].s);
		}
	}
	vis[v]=0;
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int x, y; read(n, str);
	pows.resize(n), powsi.resize(n);
	pows[0]={1, 1};
	FOR(i, 1, n) pows[i]=base*pows[i-1];
	powsi[0]={1, 1};
	FOR(i, 1, n) powsi[i]=ibase*powsi[i-1];
	adj.resize(n), nodes.resize(n), vis.assign(n, 0), dsz.resize(n), cadj.resize(n), d.resize(n), nd.resize(n), up.resize(n), down.resize(n), sum.resize(n);
	lca.init(n);
	FOR(n-1) {
		read(x, y); --x, --y;
		adj[x].pb(y), adj[y].pb(x);
		lca.ae(x, y);
	}
	d[0]=0;
	up[0]=down[0]=makeH(str[0]);
	dfsog(0);
	lca.gen();
	int ct=centroid();
	dfs(ct);
	auto checko=[&](ll x) { 
		vis.assign(n, 0);
		return x>1 ? c=x-1, dfso(ct) : true;
	};
	auto checke=[&](ll x) {
		vis.assign(n, 0);
		return x>0 ? c=x-1, dfse(ct) : true;
	};
	print(max(2*LASTTRUE(checko, 1, n)-1, 2*LASTTRUE(checke, 0, n)));
}

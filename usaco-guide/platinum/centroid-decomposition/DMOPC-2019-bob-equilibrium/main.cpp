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
#define rsz resize
#define asn assign
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

class table
{
private:
    vt<int> values;
public:
    int lo = 0, hi = 0;
    int expr = 0;

    int operator[](int idx) const
    {
        if (idx < lo)
            return 0;
        else if (idx >= hi)
            return expr;
        else
            return values[idx - lo];
    }

    void incr(int idx, int delta)
    {
        if (lo == hi)
        {
            lo = idx;
            hi = idx + 1;
            values.push_back(delta);
            return;
        }
        while (idx >= hi)
        {
            values.push_back(0);
            hi++;
        }
        if (idx < lo)
        {
            int nlo = min(2 * lo - hi, idx);
            vt<int> values2(hi - nlo);
            copy(all(values), values2.begin() + (lo - nlo));
            values = move(values2);
            lo = nlo;
        }
        values[idx - lo] += delta;
    }

    void psum()
    {
        for (int i = 1; i < sz(values); i++)
            values[i] += values[i - 1];
        expr = values.empty() ? 0 : values.back();
    }
};

int n, m, c;
vt<vt<int>> adj, cadj, dist, distc;
vt<bool> vis;
vt<int> dsz, par, dp;
LCA lca;

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

void dfs(int v) {
	dsz[v]=1;
	EACH(u, cadj[v]) {
		par[u]=v;
		dfs(u);
		dsz[v]+=dsz[u];
	}
}

void upd1(int v) {
	int t=v;
	for (; v!=-1; v=par[v]) umin(dp[v], lca.dist(t, v)); 
}

int query1(int v) {
	int ret=INT_MAX, t=v;
	for (; v!=-1; v=par[v]) umin(ret, dp[v]+lca.dist(t, v));
	return ret;
}

void upd2(int v, int x) {
	int t=v, p=v;
	if (x>=0) dist[v][min(x, dsz[v]-1)]++;
	v=par[v];
	for (; v!=-1; v=par[v], p=par[p]) {
		int d=x-lca.dist(t, v);
		if (d<0) continue;
		dist[v][min(d, dsz[v]-1)]++;
		distc[p][min(d, dsz[p])]++;
	}
}

int query2(int v) {
	int ret=0, t=v, p=v;
	ret+=dist[v][0];
	v=par[v];
	for (; v!=-1; v=par[v], p=par[p]) {
		int d=lca.dist(t, v);
		ret+=dist[v][d];
		assert(d<=dsz[p]);
		ret-=distc[p][d];
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, m);
	adj.rsz(n), cadj.rsz(n), vis.asn(n, 0), dsz.rsz(n), par.rsz(n), dp.asn(n, 1e9), dist.rsz(n), distc.rsz(n);
	lca.init(n);
	int x, y;
	FOR(n-1) {
		read(x, y); --x, --y;
		adj[x].pb(y), adj[y].pb(x);
		lca.ae(x, y);
	}
	lca.gen();
	c=centroid(); par[c]=-1;
	dfs(c);
	FOR(m) {
		read(x); --x;
		upd1(x);
	}
	FOR(n) dist[i].asn(dsz[i], 0), distc[i].asn(dsz[i]+1, 0);
	FOR(n) {
		read(x, y); --x;
		int d1=query1(i);
		int d2=lca.dist(i, x)-y-1;
		upd2(i, min(d1, d2));
	}
	FOR(n) {
		FOR(j, dsz[i]-2, -1, -1) dist[i][j]+=dist[i][j+1];
		FOR(j, dsz[i]-1, -1, -1) distc[i][j]+=distc[i][j+1];
	}
	vt<int> ans(n);
	FOR(n) ans[i]=query2(i);
	print(ans);
}
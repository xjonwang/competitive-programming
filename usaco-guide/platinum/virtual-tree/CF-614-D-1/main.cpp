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
#define eb emplace_back
#define pb push_back
#define rsz resize
#define asn assign
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

struct node {
	map<int, int, greater<int>> fac;
	int depth() const {
		int cnt=0;
		for (auto it=fac.begin(); it!=fac.end(); it++) cnt+=it->s;
		return cnt;
	}
};

bool operator==(const node& a, const node& b) {
	return a.fac==b.fac;
}

bool operator<(const node& a, const node& b) {
	int n=sz(a.fac), m=sz(b.fac);
	if (m==0) return false;
	if (n==0) return true;
	auto ita=a.fac.begin(), itb=b.fac.begin();
	for (int i=0; i<min(n, m)-1; i++, ita++, itb++) {
		if ((ita->f)!=(itb->f)) return (ita->f)>(itb->f);
		if ((ita->s)!=(itb->s)) return (ita->s)>(itb->s);
	}
	if ((ita->f)!=(itb->f)) return (ita->f)>(itb->f);
	return n!=m ? n<m : (ita->s)<(itb->s);
}

node node_lca(const node& a, const node& b) {
	node ret;
	auto ita=a.fac.begin(), itb=b.fac.begin();
	while (ita!=a.fac.end() && itb!=b.fac.end()) {
		if ((ita->f)!=(itb->f)) break;
		ret.fac[ita->f]=min(ita->s, itb->s);
		if ((ita->s)!=(itb->s)) break;
		ita++, itb++;
	}
	return ret;
}

int node_dist(const node& a, const node &b) {
	node lca=node_lca(a, b);
	return a.depth()+b.depth()-2*lca.depth();
}

#define MX 5001

bool comp[MX];
vt<int> prime;

vt<vt<pair<int, ll>>> adj;
vt<ll> dpcnt;
vt<pll> chi, par;
ll ans=LLONG_MAX;

void dfs1(int v) {
	chi[v]={dpcnt[v], 0};
	for (auto &[u, w] : adj[v]) {
		dfs1(u);
		chi[v].f+=chi[u].f;
		chi[v].s+=chi[u].s+chi[u].f*w;
	}
}

void dfs2(int v) {
	umin(ans, chi[v].s+par[v].s);
	for (auto &[u, w] : adj[v]) {
		par[u]={par[v].f+chi[v].f-chi[u].f, par[v].s+chi[v].s-(chi[u].s+chi[u].f*w)};
		par[u].s+=par[u].f*w;
		dfs2(u);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	FOR(i, 2, MX) {
		if (!comp[i]) prime.pb(i);
		EACH(p, prime) {
			if (i*p>=MX) break;
			comp[i*p]=1;
			if (i%p==0) break;
		}
	}
	int n; read(n);
	vt<int> cnt(MX, 0);
	FOR(n) {
		int x; read(x);
		cnt[x]++;
	}
	map<int, int, greater<int>> fac;
	vt<node> g;
	map<node, int> gcnt;
	g.eb(fac);
	gcnt[g.back()]=cnt[0]+cnt[1];
	FOR(i, 2, MX) {
		int t=i;
		EACH(p, prime) {
			if (p*p>t) break;
			while (t%p==0) fac[p]++, t/=p;
		}
		if (t>1 && !comp[t]) fac[t]++;
		g.eb(fac);
		gcnt[g.back()]=cnt[i];
	}
	sort(all(g));
	FOR(MX-3) g.pb(node_lca(g[i], g[i+1]));
	sort(all(g));
	g.erase(unique(all(g)), g.end());
	int m=sz(g);
	adj.rsz(m), dpcnt.rsz(m), chi.rsz(m), par.rsz(m);
	map<node, int> id;
	FOR(m) id[g[i]]=i, dpcnt[i]=gcnt[g[i]];
	FOR(i, 1, m) {
		node lca=node_lca(g[i], g[i-1]);
		adj[id[lca]].eb(id[g[i]], node_dist(lca, g[i]));
	}
	dfs1(0);
	par[0]={0, 0};
	dfs2(0);
	print(ans);
}
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

template<typename T, bool max>
struct RMQ {
	int level(int x) { return 31-__builtin_clz(x); }
	vt<T> v; vt<vt<int>> jmp;
	int cmb(int a, int b) {
		return v[a]==v[b]?min(a,b):(((v[a]<v[b])^max)?a:b); }
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

#define MX 100000

int n, m, k;
vt<pii> adj[MX];
bool vis[MX], br[MX];
int d[MX], dp[MX], ti[MX], to[MX], t, e[MX], st[MX];

void dfs(int v, int p) {
	ti[v]=t++;
	vis[v]=1;
	d[v]=d[p]+1;
	bool sc=1;
	for (auto &[u, ei] : adj[v]) {
		if (sc && u==p) {
			sc=0;
			continue;
		}
		if (!vis[u]) {
			e[u]=ei;
			dfs(u, v);
			dp[v]+=dp[u];
		} else {
			if (d[v]<d[u]) {
				dp[v]--;
			} else if (d[v]>d[u]) {
				dp[v]++;
			}
		}
	}
	to[v]=t;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, m);
	int x, y;
	FOR(m) {
		read(x, y); --x, --y;
		st[i]=x;
		adj[x].pb({y, i}), adj[y].pb({x, i});
	}
	FOR(n) {
		if (!vis[i]) {
			e[i]=-1;
			d[i]=-1;
			dfs(i, i);
		}
	}
	RMQ<int, false> inmi, outmi;
	RMQ<int, true> inma, outma;
	vt<int> vinmi(n, INT_MAX), voutmi(n, INT_MAX), vinma(n, INT_MIN), voutma(n, INT_MIN); 
	read(k);
	FOR(k) {
		read(x, y);
		y=ti[--y], x=ti[--x];
		umin(vinmi[y], x), umax(vinma[y], x);
		umin(voutmi[x], y), umax(voutma[x], y);
	}
	inmi.init(vinmi), inma.init(vinma), outmi.init(voutmi), outma.init(voutma);
	string ans(m, 'B');
	FOR(n) {
		if (dp[i]==0 && e[i]!=-1) {
			bool b=(i==st[e[i]]);
			if (inmi.query(ti[i], to[i]-1)<ti[i] || inma.query(ti[i], to[i]-1)>=to[i]) {
				ans[e[i]]=b ? 'L' : 'R';
			}
			if (outmi.query(ti[i], to[i]-1)<ti[i] || outma.query(ti[i], to[i]-1)>=to[i]) {
				ans[e[i]]=b ? 'R' : 'L';
			}
		}
	}
	print(ans);
}
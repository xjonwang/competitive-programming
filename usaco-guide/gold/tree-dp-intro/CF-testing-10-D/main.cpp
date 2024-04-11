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
#define fi first
#define sc second

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

int n, k, a=INT_MAX;
vt<int> ans;
vt<vt<int>> adj, e;
int dp[401][401];
vt<vt<pii>> dpx[401];
vt<int> pr[401][401];

void dfs(int v, int p=-1) {
	int m=sz(adj[v])-(p!=-1);
	dpx[v]=vt<vt<pii>>(m+1, vt<pii>(k, {-1, -1}));
	if (m==0) {
		if (p==-1) a=0;
		dp[v][0]=0;
		dp[v][1]=0;
		FOR(i, 2, k+1) dp[v][i]=-1;
		return;
	}
	dpx[v][0][0]={0, -1};
	FOR(m) {
		if (adj[v][i]==p) swap(adj[v][i], adj[v].back());
		int u=adj[v][i];
		dfs(u, v);
		FOR(j, k) FOR(h, k) if (dpx[v][i][j].fi!=-1 && dp[u][h]!=-1 && j+h<k && (dpx[v][i+1][j+h].fi==-1 || dpx[v][i+1][j+h].fi>dpx[v][i][j].fi+dp[u][h]+(h==0))) dpx[v][i+1][j+h]={dpx[v][i][j].fi+dp[u][h]+(h==0), j};
	}
	FOR(i, 1, k+1) dp[v][i]=dpx[v][m][i-1].fi;
	FOR(i, 1, k+1) {
		if (dp[v][i]==-1) continue;
		int curr=i-1;
		FOR(j, m, 0, -1) {
			assert(curr<k && curr>=0);
			int next=dpx[v][j][curr].sc;
			if (next==curr) {
				pr[v][i].pb(e[v][adj[v][j-1]]);
			} else {
				pr[v][i].insert(pr[v][i].end(), all(pr[adj[v][j-1]][curr-next]));
			}
			curr=next;
		}
	}
	if (dp[v][k]!=-1 && umin(a, p==-1 ? dp[v][k] : dp[v][k]+1)) {
		ans=pr[v][k];
		if (p!=-1) ans.pb(e[v][p]);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, k);
	adj.resize(n), e.resize(n, vt<int>(n));
	int x, y;
	FOR(n-1) {
		read(x, y); --x, --y;
		e[x][y]=e[y][x]=i+1;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	dfs(0);
	print(a);
	print(ans);
}
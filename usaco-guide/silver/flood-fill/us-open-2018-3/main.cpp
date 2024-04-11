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
 
ll n, compCnt, cnt, sz, ans1, ans2, c1, c2;
vt<vt<ll>> grid, comp;
vt<vt<vt<ll>>> adj;
vt<ll> color, sizes;
vt<vt<bool>> vis1;
vt<bool> vis;
unordered_set<ll> trip;
const int dr[4]={1, -1, 0, 0}, dc[4]={0, 0, 1, -1};
 
void flood(ll r, ll c, ll x) {
	if (r<0 || r>=n || c<0 || c>=n) return;
	if (grid[r][c]!=x) {
		if (comp[r][c]!=-1) {
			adj[comp[r][c]].pb({x, compCnt, cnt});
			adj[compCnt].pb({grid[r][c], comp[r][c], cnt});
			cnt++;
		}
		return;
	}
	if (vis1[r][c]) return;
	vis1[r][c]=1;
	comp[r][c]=compCnt;
	sz++;
	FOR(4) flood(r+dr[i], c+dc[i], x);
}

void dfs(ll v) {
	if (trip.count(v)) return;
	sz+=sizes[v];
	trip.insert(v);
	ll a=c1==color[v] ? c2 : c1;
	vt<ll> temp={a, 0ll, 0ll};
	auto it=lower_bound(all(adj[v]), temp);
	while (it!=adj[v].end() && it->front()==a) {
		vis[it->operator[](2)]=1;
		dfs(it->operator[](1));
		it++;
	}
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("multimoo.in", "r", stdin);
	freopen("multimoo.out", "w", stdout);
	read(n);
	grid.resize(n, vt<ll>(n)), comp.resize(n, vt<ll>(n, -1)), adj.resize(n*n), vis1.resize(n, vt<bool>(n, 0));
	FOR(n) FOR(j, n) cin >> grid[i][j];
	FOR(n) {
		FOR(j, n) {
			if (comp[i][j]==-1) {
				sz=0;
				color.pb(grid[i][j]);
				flood(i, j, grid[i][j]);
				sizes.pb(sz);
				ans1=max(ans1, sz);
				compCnt++;
			}
		}
	}
	vis.resize(cnt, 0);
	FOR(compCnt) {
		sort(all(adj[i]));
		adj[i].erase(unique(all(adj[i])), adj[i].end());
	}
	FOR(compCnt) {
		EACH(e, adj[i]) {
			if (!vis[e[2]]) {
				c1=e[0], c2=color[i], sz=0;
				trip.clear();
				dfs(i);
				ans2=max(ans2, sz);
			}
		}
	}
	print(ans1);
	print(ans2);
}
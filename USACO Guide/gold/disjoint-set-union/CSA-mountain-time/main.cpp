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

int n, m;
vt<vt<int>> g, mt;
vt<vt<pii>> p;
vt<vt<bool>> vis;

int dr[4]={1, -1, 0, 0}, dc[4]={0, 0, 1, -1};

struct dsu {
	vt<int> e, r;
	vt<list<int>> v;
	dsu(int n) : e(vt<int>(n, -1)), r(vt<int>(n)), v(vt<list<int>>(n)) {}
	int get(int x) { return e[x]<0 ? x : e[x]=get(e[x]); }
	int size(int x) { return e[x]<0 ? -e[x] : size(e[x]); }
	bool unite(int x, int y, int c) {
		x=get(x), y=get(y);
		if (x==y) return false;
		if (e[x]>e[y]) swap(x, y);
		if (r[x]==r[y]) {
			v[x].splice(v[x].end(), v[y]);
		} else if (r[x]<r[y]) {
			EACH(p, v[x]) mt[p/m][p%m]=c;
			v[x]=move(v[y]);
		} else {
			EACH(p, v[y]) mt[p/m][p%m]=c;
		}
		r[x]=max(r[x], r[y]);
		e[x]+=e[y];
		e[y]=x;
		return true;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, m);
	g.assign(n, vt<int>(m)), mt.assign(n, vt<int>(m, 0)), vis.assign(n, vt<bool>(m, 0));
	p.resize(1e6+1);
	int x;
	FOR(n) {
		FOR(j, m) {
			read(x);
			g[i][j]=x; p[x].pb({i, j});
		}
	}
	dsu d(n*m);
	FOR(i, 1e6, -1, -1) {
		for (auto [pr, pc] : p[i]) {
			d.r[pr*m+pc]=i;
			d.v[pr*m+pc].pb(pr*m+pc);
			FOR(k, 4) {
				int r=pr+dr[k], c=pc+dc[k];
				if (r>=0 && r<n && c>=0 && c<m && vis[r][c]) d.unite(pr*m+pc, r*m+c, i);
			}
			vis[pr][pc]=1;
		}
	}
	FOR(n) FOR(j, m) mt[i][j]=g[i][j]-mt[i][j];
	EACH(a, mt) print(a);
}
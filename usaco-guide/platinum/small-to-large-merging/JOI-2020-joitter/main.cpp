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

ll nc2(ll x) {
	return x*(x-1)/2;
}

struct DSU {
	ll cnt;
	vt<int> e;
	vt<unordered_set<int>> in, incc, outcc;
	DSU(int n) : cnt(0), e(n, -1), in(n), incc(n), outcc(n) {
		FOR(n) in[i].insert(i);
	}
	int get(int x) { return e[x]<0 ? x : e[x]=get(e[x]); }
	int size(int x) { return e[x]<0 ? -1*e[x] : size(e[x]); }
	ll value(int x) {
		x=get(x);
		return 2*nc2(size(x))+1ll*(sz(in[x])-size(x))*size(x);
	}
	void unite(int x, int y) {
		x=get(x), y=get(y);
		if (x==y) return;
		cnt-=value(x)+value(y);
		if (e[x]>e[y]) swap(x, y);
		e[x]+=e[y];
		e[y]=x;
		unordered_set<int> q;
		EACH(u, incc[y]) {
			outcc[u].erase(y), outcc[u].insert(x), incc[x].insert(u);
			if (outcc[x].count(u)) q.insert(u);
		}
		EACH(u, outcc[y]) {
			incc[u].erase(y), incc[u].insert(x), outcc[x].insert(u);
			if (incc[x].count(u)) q.insert(u);
		}
		incc[y].clear();
		outcc[y].clear();
		if (sz(in[x])<sz(in[y])) swap(in[x], in[y]);
		in[x].insert(all(in[y]));
		cnt+=value(x);
		EACH(u, q) unite(u, x);
	}
	void ae(int x, int y) {
		int cx=get(x), cy=get(y);
		if (cx==cy) return;
		if (incc[cx].count(cy)) {
			unite(cx, cy);
		} else {
			cnt-=value(cy);
			in[y].insert(x), incc[cy].insert(cx), outcc[cx].insert(cy);
			cnt+=value(cy);
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m; read(n, m);
	DSU dsu(n);
	FOR(m) {
		int x, y; read(x, y);
		dsu.ae(--x, --y);
		print(dsu.cnt);
	}
}
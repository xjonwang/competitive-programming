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
#define pld pair<ld, ld>
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

int ans;

void solve(int n, int m, int k, vt<vt<int>>& v) {
	vt<vt<int>> pre(n+1, vt<int>(m+1, 0));
	FOR(n) FOR(j, m) pre[i+1][j+1]=v[i][j]+pre[i+1][j]+pre[i][j+1]-pre[i][j];
	vt<int> y1(n, 0), y2(n, 0), x1(m, 0), x2(m, 0);
	FOR(i, k-1, n) FOR(j, k-1, m) umax(y1[i], pre[i+1][j+1]-pre[i+1][j-k+1]-pre[i-k+1][j+1]+pre[i-k+1][j-k+1]), umax(y2[i-k+1], pre[i+1][j+1]-pre[i+1][j-k+1]-pre[i-k+1][j+1]+pre[i-k+1][j-k+1]);
	FOR(i, 1, n) umax(y1[i], y1[i-1]);
	FOR(i, n-2, -1, -1) umax(y2[i], y2[i+1]);
	int a=0, p=0;
	FOR(i, k-1, n-k) {
		FOR(j, k-1, m) umax(x1[j], pre[i+1][j+1]-pre[i+1][j-k+1]-pre[i-k+1][j+1]+pre[i-k+1][j-k+1]), umax(x2[j-k+1], pre[i+1][j+1]-pre[i+1][j-k+1]-pre[i-k+1][j+1]+pre[i-k+1][j-k+1]);
		FOR(j, 1, m) umax(x1[j], x1[j-1]);
		FOR(j, m-2, -1, -1) umax(x2[j], x2[j+1]);
		FOR(j, k-1, m-k) umax(p, x1[j]+x2[j+1]);
		if (i-k>=k-1) FOR(j, k-1, m) umax(p, pre[i+1][j+1]-pre[i+1][j-k+1]-pre[i-k+1][j+1]+pre[i-k+1][j-k+1]+y1[i-k]);
		umax(a, p+y2[i+1]);
	}
	umax(ans, a);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, k; read(n, m, k);
	vt<vt<int>> v(n, vt<int>(m)); read(v);
	solve(n, m, k, v);
	FOR(n/2) swap(v[i], v[n-1-i]);
	solve(n, m, k, v);
	FOR(n/2) swap(v[i], v[n-1-i]);
	vt<vt<int>> t(m, vt<int>(n));
	FOR(m) FOR(j, n) t[i][j]=v[j][i];
	solve(m, n, k, t);
	FOR(m/2) swap(t[i], t[m-1-i]);
	solve(m, n, k, t);
	print(ans);
}
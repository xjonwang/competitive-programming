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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, b, x, y; read(n, m); b=n/2;
	vt<int> adjl(n, 0), adjr(n, 0);
	FOR(m) {
		read(x, y);
		if (y>=b) adjr[x]^=1<<(y-b);
		else adjl[x]^=1<<y;
		if (x>=b) adjr[y]^=1<<(x-b);
		else adjl[y]^=1<<x;
	}
	vt<int> excl(1<<(n-b), -1);
	vt<pii> dp(1<<b, {-1, -1}), incl(1<<b);
	dp[0]={0, 0}, excl[0]=0;
	int idx;
	FOR(i, 1, 1<<(n-b)) {
		idx=__builtin_ctz(i);
		int t=excl[i^(1<<idx)];
		if (t<0 || adjr[b+idx] & i) continue;
		excl[i]=t|adjl[b+idx];
		if (dp[((1<<b)-1)^excl[i]].f < __builtin_popcount(i)) dp[((1<<b)-1)^excl[i]]={__builtin_popcount(i), i};
	}
	incl[0]={0, 0};
	FOR(i, 1, 1<<b) {
		int a=0, e=0;
		FOR(j, b) {
			if (i & (1<<j)) {
				pii t=incl[i^(1<<j)];
				if (t.s & (1<<j)) {
					if (__builtin_popcount(t.f)>__builtin_popcount(a)) {
						a=t.f;
						e=t.s;
					}
				} else {
					if (__builtin_popcount(t.f)+1>__builtin_popcount(a)) {
						a=t.f|(1<<j);
						e=t.s|adjl[j];
					}
				}
			}
		}
		incl[i]={a, e};
	}
	int ans=0, l, r;
	FOR(1<<b) {
		if (umax(ans, dp[i].f+__builtin_popcount(incl[i].f))) {
			l=incl[i].f;
			r=dp[i].s;
		}
	}
	print(ans);
	FOR(b) if (l & (1<<i)) cout << i << " ";
	FOR(n-b) if (r & (1<<i)) cout << b+i << " ";
}
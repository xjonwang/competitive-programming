#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define ar array
#define str string

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;

template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define vt vector
#define eb emplace_back
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

void round1(set<pii>& l, set<pii>& r, vt<int>& ans) {
	for (auto itl=l.begin(); itl!=l.end();) {
		auto [x1, i1]=*itl;
		auto itr=r.lower_bound(*itl);
		if (itr!=r.begin()) {
			auto [x2, i2]=*prev(itr);
			ans[i1]=ans[i2]=(x1-x2)/2;
			r.erase(prev(itr));
			itl=l.erase(itl);
		} else {
			itl++;
		}
	}
}

void round2l(set<pii>& l, vt<int>& ans) {
	for (auto it=l.begin(); it!=l.end() && next(it)!=l.end(); it=l.erase(l.erase(it))) {
		auto [x1, i1]=*it;
		auto [x2, i2]=*next(it);
		ans[i1]=ans[i2]=x1+(x2-x1)/2;
	}
}

void round2r(set<pii>& r, vt<int>& ans) {
	for (auto it=r.rbegin(); it!=r.rend() && next(it)!=r.rend(); it=next(next(it))) {
		auto [x1, i1]=*it;
		auto [x2, i2]=*next(it);
		ans[i1]=ans[i2]=m-x1+(x1-x2)/2;
	}
	for (auto it=sz(r)&1 ? next(r.begin()) : r.begin(); it!=r.end(); it=r.erase(it));
}

void solve() {
	read(n, m);
	vt<int> v1(n); read(v1);
	vt<char> v2(n); read(v2);
	set<pii> le, lo, re, ro;
	FOR(n) {
		switch (v2[i]) {
			case 'L':
				if (v1[i]&1) lo.insert({v1[i], i});
				else le.insert({v1[i], i});
				break;
			case 'R':
				if (v1[i]&1) ro.insert({v1[i], i});
				else re.insert({v1[i], i});
				break;
		}
	}
	vt<int> ans(n, -1);
	round1(le, re, ans);
	round1(lo, ro, ans);
	round2l(le, ans);
	round2l(lo, ans);
	round2r(re, ans);
	round2r(ro, ans);
	if (sz(lo) && sz(ro)) {
		auto [x1, i1]=*lo.begin();
		auto [x2, i2]=*ro.begin();
		ans[i1]=ans[i2]=(m+x1+m-x2)/2;
	}
	if (sz(le) && sz(re)) {
		auto [x1, i1]=*le.begin();
		auto [x2, i2]=*re.begin();
		ans[i1]=ans[i2]=(m+x1+m-x2)/2;
	}
	print(ans);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}
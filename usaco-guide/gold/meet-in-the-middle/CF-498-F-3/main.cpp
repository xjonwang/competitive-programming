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

int n;
vt<ar<int, 3>> v;
vt<string> mp={"MW", "LW", "LM"};

void construct(int idx, int end, ar<int, 3> val, vt<int>& seq, vt<pair<ar<int, 3>, vt<int>>>& cnt) {
	if (idx==end) {
		cnt.pb({{val[1]-val[0], val[2]-val[0], val[0]}, seq});
		return;
	}
	FOR(3) {
		val[i]+=v[idx][i];
		seq.pb(i);
		construct(idx+1, end, val, seq, cnt);
		seq.pop_back();
		val[i]-=v[idx][i];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n);
	v.resize(n); read(v);
	ar<int, 3> sum={0,0,0};
	FOR(n) FOR(j, 3) sum[j]+=v[i][j];
	vt<pair<ar<int, 3>, vt<int>>> v1, v2;
	vt<int> t;
	construct(0, n/2, {0, 0, 0}, t, v1);
	construct(n/2, n, {0, 0, 0}, t, v2);
	sort(all(v2));
	int m=INT_MAX;
	vt<int> ans(n);
	EACH(x, v1) {
		auto it=lower_bound(all(v2), make_pair(ar<int, 3>({-x.f[0]+sum[1]-sum[0], -x.f[1]+sum[2]-sum[0], INT_MIN}), vt<int>()));
		if (sum[0]==sum[1]-it->f[0]-x.f[0] && sum[0]==sum[2]-it->f[1]-x.f[1] && umin(m, x.f[2]+it->f[2])) {
			FOR(n/2) ans[i]=x.s[i];
			FOR(i, n-n/2) ans[n/2+i]=it->s[i];
		}
	}
	if (m==INT_MAX) print("Impossible");
	else EACH(x, ans) print(mp[x]);
}
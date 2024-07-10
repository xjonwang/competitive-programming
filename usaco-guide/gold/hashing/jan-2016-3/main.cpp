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

#define MOD ((int)1e9+7)

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

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

using H = ar<int,2>; // bases not too close to ends 
H makeH(char c) { return {c,c}; }
uniform_int_distribution<int> BDIST(0.1*MOD,0.9*MOD);
const H base{BDIST(rng),BDIST(rng)};
H operator+(H l, H r) { 
	FOR(2) if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
	return l; }
H operator-(H l, H r) { 
	FOR(2) if ((l[i] -= r[i]) < 0) l[i] += MOD;
	return l; }
H operator*(H l, H r) { 
	FOR(2) l[i] = (ll)l[i]*r[i]%MOD;
	return l; }

vt<H> pows{{1,1}};

struct HashRange {
	str S; vt<H> cum{{}};
	void add(char c) { S += c; cum.pb(base*cum.back()+makeH(c)); }
	void add(str s) { EACH(c,s) add(c); }
	void extend(int len) { while (sz(pows) <= len) 
		pows.pb(base*pows.back()); }
	H hash(int l, int r) { int len = r+1-l; extend(len);
		return cum[r+1]-pows[len]*cum[l]; }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	//freopen("lightsout.in", "r", stdin);
	//freopen("lightsout.out", "w", stdout);
	int n; read(n);
	vt<pii> v(n); read(v);
	vt<int> d(n), t(n);
	FOR(i, 1, n) d[i]=abs(v[i].f-v[i-1].f)+abs(v[i].s-v[i-1].s);
	d[0]=abs(v[0].f-v[n-1].f)+abs(v[0].s-v[n-1].s);
	FOR(n) {
		int prev=((i-1)%n+n)%n, next=(i+1)%n;
		if ((v[prev].f - v[i].f) * (v[next].s - v[i].s) - (v[next].first - v[i].f) * (v[prev].s - v[i].s) > 0) t[i]=1;
		else t[i]=-1;
	}
	vt<int> cw(n), ccw(n); cw[0]=0, ccw[n-1]=d[0];
	FOR(i, 1, n) cw[i]=cw[i-1]+d[i];
	FOR(i, n-2, -1, -1) ccw[i]=ccw[i+1]+d[i+1];
	int ans=0;
	FOR(i, 1, n) {
		vt<bool> p(n, 1); p[i]=0;
		int j=1, cnt=n-2, r;
		for (; j<n-i; j++) {
			int m=0;
			FOR(k, 1, n) {
				if (p[k]) {
					if (k+j>=n || d[k+j]!=d[i+j] || t[k+j]!=t[i+j]) {
						umax(m, min(d[(k+j)%n], d[i+j]));	
						p[k]=0;
						cnt--;
					}
				}
			}
			r=m;
			if (cnt==0) break;
		}
		if (i+j==n) umax(ans, ccw[0]-cw[i] - min(cw[i], ccw[i])); 
		else umax(ans, cw[i+j-1]-cw[i]+r+min(cw[i+j-1]+r, ccw[i+j-1]-r) - min(cw[i], ccw[i]));
	}
	print(ans);
}
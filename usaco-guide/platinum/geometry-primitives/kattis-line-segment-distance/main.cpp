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

template<typename T>
using point=complex<T>;
#define X real()
#define Y imag()

ll sign(ll x) {
	if (x<0) return -1;
	else if (x>0) return 1;
	else return 0;
}

template<typename T>
T cp(point<T> a, point<T> b) {
	return (conj(a)*b).Y;
}

template<typename T>
T dp(point<T> a, point<T> b) {
	return (conj(a)*b).X;
}

template<typename T>
bool cmp(const point<T>& a, const point<T>& b) {
	return a.X!=b.X ? a.X<b.X : a.Y<b.Y;
}

pair<bool, point<ld>> intersect(point<ll> a1, point<ll> a2, point<ll> b1, point<ll> b2) {
	if (sign(cp(b1-a1, b1-a2))==0 && sign(cp(b2-a1, b2-a2))==0) {
		if (cmp(a1, b1)!=cmp(a2, b1) || cmp(a1, b2)!=cmp(a2, b2) || cmp(b1, a1)!=cmp(b2, a1) || cmp(b1, a2)!=cmp(b2, a2)) {
			vt<point<ll>> v{a1, a2, b1, b2};
			sort(all(v), cmp<ll>);
			return {1, point<ld>(v[1].X, v[1].Y)};
		} else {
			return {0, point<ld>(0, 0)};
		}
	}
	ll cp1=sign(cp(b1-a1, b1-a2));
	ll cp2=sign(cp(b2-a1, b2-a2));
	ll cp3=sign(cp(a1-b1, a1-b2));
	ll cp4=sign(cp(a2-b1, a2-b2));
	if (cp1*cp2>0 || cp3*cp4>0) {
		return {0, point<ld>(0, 0)};
	} else {
		point<ld> p1=point<ld>(a1.X, a1.Y), p2=point<ld>(a2.X, a2.Y), q1=point<ld>(b1.X, b1.Y), q2=point<ld>(b2.X, b2.Y);
		point<ld> p=(p1*cp(p2-q1, p2-q2)+p2*cp(q1-p1, q1-q2))/(cp(p2-q1, p2-q2)+cp(q1-p1, q1-q2));
		return {true, p};
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; read(n);
	ll x1, y1, x2, y2, x3, y3, x4, y4;
	cout << fixed << setprecision(2);
	FOR(n) {
		read(x1, y1, x2, y2, x3, y3, x4, y4);
		point<ll> a1(x1, y1), a2(x2, y2), b1(x3, y3), b2(x4, y4);
		auto [b, a]=intersect(a1, a2, b1, b2);
		if (b) {
			print(a.X, a.Y);
		} else {
			print("none");
		}
	}
}
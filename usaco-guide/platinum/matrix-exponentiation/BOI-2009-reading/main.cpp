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

#define MOD 1000000007
#define DIM 131
#define ALPH 26
#define LB 5

using vec=ar<ll, DIM>;
using mat=ar<ar<ll, DIM>, DIM>;

template<typename T, std::size_t N>
constexpr ar<T, N> make_filled_array(T value) {
    ar<T, N> arr{};
	FOR(N) arr[i]=value;
    return arr;
}
template<typename T, std::size_t N>
constexpr ar<ar<T, N>, N> make_identity() {
	ar<ar<T, N>, N> arr{};
	FOR(N) FOR(j, N) arr[i][j]=0;
	FOR(N) arr[i][i]=1;
	return arr;
}


constexpr vec ZERO_VEC{make_filled_array<ll, DIM>(0)};
constexpr mat ZERO_MAT{make_filled_array<ar<ll, DIM>, DIM>(ZERO_VEC)};
constexpr mat ID{make_identity<ll, DIM>()};

mat matmul(const mat &a, const mat &b) {
	mat ret(ZERO_MAT);
	FOR(DIM) FOR(j, DIM) FOR(k, DIM) ret[i][j]+=a[i][k]*b[k][j], ret[i][j]%=MOD;
	return ret;
}

vec matmul(const vec &a, const mat &b) {
	vec ret(ZERO_VEC);
	FOR(DIM) FOR(j, DIM) ret[i]+=a[j]*b[i][j], ret[i]%=MOD;
	return ret;
}

mat matexp(mat x, int e) {
	mat ret(ID);
	FOR(30) {
		if (e&(1<<i)) ret=matmul(ret, x);
		x=matmul(x, x);
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m; read(n, m);
	vt<vt<int>> d(26, vt<int>(26, 1));
	char x, y; int z;
	FOR(m) {
		read(x, y, z); x-='a', y-='a';
		d[x][y]=z, d[y][x]=z;
	}
	mat t(ZERO_MAT);
	FOR((LB-1)*ALPH) t[i][i+ALPH]=1;
	FOR(26) {
		FOR(j, LB*ALPH) {
			if (j/ALPH+d[j%ALPH][i]==5) t[(LB-1)*ALPH+i][j]=1;
		}
	}
	FOR(i, (LB-1)*ALPH, DIM) t[LB*ALPH][i]=1;
	t=matexp(t, n+1);
	vec st(ZERO_VEC);
	FOR(i, (LB-1)*ALPH, LB*ALPH) st[i]=1;
	st=matmul(st, t);
	print(st[LB*ALPH]);
}
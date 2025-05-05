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
#define rsz resize
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

ll inv(ll a, ll b) {
	return 1<a ? b-inv(b%a, a)*b/a : 1;
}

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

using H = ar<int,2>; // bases not too close to ends 
H makeH(char c) { return {c,c}; }
uniform_int_distribution<int> BDIST(0.1*MOD,0.9*MOD);
const H base{BDIST(rng),BDIST(rng)};
const H ibase{(int)inv(base[0], MOD), (int)inv(base[1], MOD)};
H operator+(H l, H r) { 
	FOR(2) if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
	return l; }
H operator-(H l, H r) { 
	FOR(2) if ((l[i] -= r[i]) < 0) l[i] += MOD;
	return l; }
H operator*(H l, H r) { 
	FOR(2) l[i] = (ll)l[i]*r[i]%MOD;
	return l; }

vt<H> pows{{1,1}}, ipows{{1, 1}};

struct HashRange {
	int n;
	vt<int> S;
	vt<H> cum;
	void init(const vt<char>& x) { 
		n=sz(x);
		extend(sz(x));
		cum.rsz(sz(x)+1);
		cum[0]={0, 0};
		FOR(sz(x)) cum[i+1]=cum[i]+pows[i]*makeH(x[i]);
	}
	void init(const vt<H>& x) {
		n=sz(x);
		extend(sz(x));
		cum.rsz(sz(x)+1);
		cum[0]={0, 0};
		FOR(sz(x)) cum[i+1]=cum[i]+x[i];
	}
	void extend(int len) {
		while (sz(pows) <= len) pows.pb(base*pows.back()), ipows.pb(ibase*ipows.back());
	}
	H hash(int l, int len, int mul=1) {
		assert(len<=n);
		return (cum[min(l+len, n)]-cum[l])*ipows[l*mul]+(l+len>n ? cum[(l+len)%n]*pows[(n-l)*mul] : makeH(0)); 
	}
};

struct GridHash {
	int n, m;
	vt<HashRange> rows;
	vt<HashRange> columns;
	void init(const vt<vt<char>>& x) {
		n=sz(x), m=sz(x[0]);
		extend(n*m);
		rows.rsz(n);
		columns.rsz(m);
		FOR(n) rows[i].init(x[i]);
		FOR(m) {
			vt<H> sums(n);
			FOR(j, n) sums[j]=pows[j*m]*rows[j].hash(i, m);
			columns[i].init(sums);
		}
	}
	void extend(int len) {
		while (sz(pows) <= len) pows.pb(base*pows.back()), ipows.pb(ibase*ipows.back());
	}
	H hash(int l, int len) {
		int sr=l/m, sc=l%m, rlen=len/m, clen=len%m;
		H rhash=columns[sc].hash(sr, rlen, m);
		H chash=pows[rlen*m]*rows[(sr+rlen)%n].hash(sc, clen);
		return rhash+chash;
	}
};

int n, m;

pii calc_idx(pii l, int len) {
	int dr=len/m, dc=len%m;
	return {(l.f+dr)%n, (l.s+dc)%m};
}

int calc_idx(pii x) {
	return m*x.f+x.s;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, m);
	vt<vt<char>> v(n, vt<char>(m)); read(v);
	GridHash gh; gh.init(v);
	pii ans={0, 0};
	FOR(n) {
		FOR(j, m) {
			auto check=[&](ll len) {
				return gh.hash(calc_idx(ans), len)==gh.hash(calc_idx({i, j}), len);
			};
			int len=LASTTRUE(check, 0, n*m);
			pii idx1=calc_idx(ans, len), idx2=calc_idx({i, j}, len);
			if (len<n*m && v[idx1.f][idx1.s]>v[idx2.f][idx2.s]) ans={i, j};
		}
	}
	vt<vt<char>> a(n, vt<char>(m));
	FOR(n) {
		FOR(j, m) {
			pii idx=calc_idx(ans, calc_idx({i, j}));
			a[i][j]=v[idx.f][idx.s];
		}
	}
	FOR(n) {
		FOR(j, m) write(a[i][j]);
		print();
	}
}
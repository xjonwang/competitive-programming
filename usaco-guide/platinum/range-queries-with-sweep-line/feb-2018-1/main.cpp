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
#define asn assign
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

struct ST {
	int n;
	vt<ll> v;
	ST(int n) : n(n), v(2*n, 1e18) {}
	void reset() {
		v.asn(2*n, 1e18);
	}
	void minify(int i, ll x) {
		if (umin(v[i+=n], x)) {
			for (; i>>=1;) {
				v[i]=min(v[i<<1], v[i<<1|1]);
			}
		}
	}
	ll query(int l, int r) {
		ll ret=1e18;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) umin(ret, v[l++]);
			if (r&1) umin(ret, v[--r]);
		}
		return ret;
	}
};

struct sl {
	int l, r, w;
};

struct qu {
	int l, r, idx;
};

#define MX 1000000000

void solve(vt<sl>& vsl, vt<qu>& vqu, vt<ll>& ans) {
	vt<int> ridx;
	for (auto &[l, r, _] : vsl) ridx.pb(l), ridx.pb(r);
	for (auto &[l, r, _] : vqu) ridx.pb(l), ridx.pb(r);
	sort(all(ridx));
	ridx.erase(unique(all(ridx)), ridx.end());
	int n=sz(ridx);
	map<int, int> idx;
	FOR(n) idx[ridx[i]]=i;
	ST over(n), under(n);
	map<int, vt<sl>> slmp;
	EACH(x, vsl) slmp[x.l].pb(x);
	map<int, vt<qu>> qump;
	EACH(x, vqu) qump[x.l].pb(x);
	EACH(x, ridx) {
		for (auto &[l, r, w] : slmp[x]) {
			over.minify(idx[r], w+r-l);
			under.minify(idx[r], w-r-l);
		}
		for (auto &[l, r, i] : qump[x]) {
			umin(ans[i], (ll)(r-l));
			umin(ans[i], over.query(idx[r], n)-r+l);
			umin(ans[i], under.query(0, idx[r]+1)+r+l);
		}
	}
	reverse(all(ridx));
	over.reset(), under.reset();
	EACH(x, ridx) {
		for (auto &[l, r, w] : slmp[x]) {
			over.minify(idx[r], w+r+l);
			under.minify(idx[r], w-r+l);
		}
		for (auto &[l, r, i] : qump[x]) {
			umin(ans[i], (ll)(r-l));
			umin(ans[i], over.query(idx[r], n)-r-l);
			umin(ans[i], under.query(0, idx[r]+1)+r-l);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("slingshot.in", "r", stdin);
	freopen("slingshot.out", "w", stdout);
	int n, m; read(n, m);
	vt<sl> sl1, sl2;
	FOR(n) {
		int x, y, z; read(x, y, z);
		if (x<y) sl1.pb({x, y, z});
		else sl2.pb({MX-x, MX-y, z});
	}
	vt<qu> qu1, qu2;
	FOR(m) {
		int x, y; read(x, y);
		if (x<y) qu1.pb({x, y, i});
		else qu2.pb({MX-x, MX-y, i});
	}
	vt<ll> ans(m, LLONG_MAX);
	solve(sl1, qu1, ans);
	solve(sl2, qu2, ans);
	EACH(a, ans) print(a);
}
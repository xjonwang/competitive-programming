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

#define MOD 998244353

struct ST {
	int n, h; vt<ll> sum, mi, d;
	ST(vt<int>& a) : n(1) {
		while (n<sz(a)) n*=2;
		h=32-__builtin_clz(n);
		d.assign(n, 0);
		sum=mi=vt<ll>(2*n, 0);
		FOR(sz(a)) sum[n+i]=mi[n+i]=a[i];
		FOR(i, n-1, 0, -1) sum[i]=sum[i<<1]+sum[i<<1|1], mi[i]=min(mi[i<<1], mi[i<<1|1]);
	}
	ll size(int i) {
		return 1<<(h-(32-__builtin_clz(i)));
	}
	void apply(int i, ll x) {
		sum[i]+=x*size(i), mi[i]+=x;
		if (i<n) d[i]+=x;
	}
	ll calc_sum(int i) {
		if (i>=n) return sum[i];
		return sum[i<<1]+sum[i<<1|1]+size(i)*d[i];
	}
	ll calc_min(int i) {
		if (i>=n) return mi[i];
		return min(mi[i<<1], mi[i<<1|1])+d[i];
	}
	void push(int i) {
		apply(i<<1, d[i]);
		apply(i<<1|1, d[i]);
		d[i]=0;
	}
	void propagate(int i) {
		FOR(j, h, 0, -1) push(i>>j);
	}
	void build(int i) {
		while (i>1) i>>=1, sum[i]=calc_sum(i), mi[i]=calc_min(i);
	}
	void modify(int l, int r, ll x) {
		int l0=l+n, r0=r+n-1;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) apply(l++, x);
			if (r&1) apply(--r, x);
		}
		build(l0), build(r0);
	}
	ll query_sum(int l, int r) {
		ll ret=0;
		propagate(l+n), propagate(r+n-1);
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) ret+=sum[l++];
			if (r&1) ret+=sum[--r];
		}
		return ret;
	}
	ll query_max(int l, int r) {
		ll ret=LLONG_MAX;
		propagate(l+n), propagate(r+n-1);
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) umin(ret, mi[l++]);
			if (r&1) umin(ret, mi[--r]);
		}
		return ret;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("haybales.in", "r", stdin);
	freopen("haybales.out", "w", stdout);
	int n, m, x, y, z; read(n, m);
	vt<int> v(n); read(v);
	ST st(v);
	char a;
	FOR(m) {
		read(a);
		switch (a) {
			case 'P':
				read(x, y, z); --x;
				st.modify(x, y, z);
				break;
			case 'M':
				read(x, y); --x;
				print(st.query_max(x, y));
				break;
			case 'S':
				read(x, y); --x;
				print(st.query_sum(x, y));
				break;
		}
	}
}
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

using H = ar<int,2>;
constexpr H ZERO={0, 0};
H makeH(int a, int b) { return {a, b}; }
H operator+(H l, H r) { 
	FOR(2) if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
	return l; }
H& operator+=(H& l, const H& r) { 
	FOR(2) if ((l[i] += r[i]) >= MOD) l[i] -= MOD;
	return l; }
H operator-(H l, H r) { 
	FOR(2) if ((l[i] -= r[i]) < 0) l[i] += MOD;
	return l; }
H& operator-=(H& l, const H& r) { 
	FOR(2) if ((l[i] -= r[i]) < 0) l[i] += MOD;
	return l; }
H operator*(H l, H r) {
	FOR(2) l[i] = (ll)l[i]*r[i]%MOD;
	return l; }
H& operator*=(H& l, const H& r) {
	FOR(2) l[i] = (ll)l[i]*r[i]%MOD;
	return l; }
bool operator<(H a, H b) {
	return a[0]<b[0]; }
bool operator<=(H a, H b) {
	return a[0]<=b[0]; }

struct ST {
	int n, h;
	vt<H> v, ls, la;
	ST(int a) : n(1) {
		while (n<a) n<<=1;
		h=32-__builtin_clz(n);
		v.assign(2*n, {INT_MAX, -1}), ls.assign(2*n, {0, 0}), la.assign(2*n, {0, 0});
	}
	void apply_set(int i, H x) {
		v[i]=x;
		if (i<n) ls[i]=x, la[i]={0, 0};
	}
	void apply_add(int i, H x) {
		v[i]+=x;
		if (i<n) la[i]+=x;
	}
	void build(int i) {
		for (; i>>=1;) {
			if (ls[i]!=ZERO) v[i]=ls[i];
			else v[i]=max(v[i<<1], v[i<<1|1]);
			if (la[i]!=ZERO) v[i]+=la[i];
		}
	}
	void push(int i) {
		if (ls[i]!=ZERO) {
			apply_set(i<<1, ls[i]);
			apply_set(i<<1|1, ls[i]);
			ls[i]={0, 0};
		}
		if (la[i]!=ZERO) {
			apply_add(i<<1, la[i]);
			apply_add(i<<1|1, la[i]);
			la[i]={0, 0};
		}
	}
	void propagate(int i) {
		FOR(j, h-1, 0, -1) {
			push(i>>j);
		}
	}
	void add(int l, int r, H x) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		propagate(l0);
		propagate(r0);
		for(; l<r; l>>=1, r>>=1) {
			if (l&1) apply_add(l++, x);
			if (r&1) apply_add(--r, x);
		}
		build(l0);
		build(r0);
	}
	void set(int l, int r, H x) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		propagate(l0);
		propagate(r0);
		for(; l<r; l>>=1, r>>=1) {
			if (l&1) apply_set(l++, x);
			if (r&1) apply_set(--r, x);
		}
		build(l0);
		build(r0);
	}
	H query(int l, int r) {
		l+=n, r+=n;
		propagate(l);
		propagate(r-1);
		H ret={INT_MAX, -1};
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) umin(ret, v[l++]);
			if (r&1) umin(ret, v[--r]);
		}
		return ret;
	}
	int lower_bound(H x) {
		if (v[1]<x) return n;
		int idx=1;
		while (idx<n) {
			push(idx);	
			if (v[idx<<1]<x) idx<<=1, idx|=1;
			else idx<<=1;
		}
		return idx-n;
	}
	int upper_bound(H x) {
		if (v[1]<=x) return n;
		int idx=1;
		while (idx<n) {
			push(idx);	
			if (v[idx<<1]<=x) idx<<=1, idx|=1;
			else idx<<=1;
		}
		return idx-n;
	}
};

void solve() {
	int n, m; read(n, m);
	vt<int> a(n), b(m); read(a, b);
	vt<ll> pre(n+1); pre[0]=0;
	FOR(n) pre[i+1]=pre[i]+a[i];
	vt<ST> dp(m, n+1);
	dp[0].set(0, 1, {0, 1});
	FOR(n) {
		H x={INT_MAX, -1};
		FOR(j, m) {
			H y=dp[j].query(i, i+1);
			if (y[0]!=INT_MAX) {
				if (x[0]>y[0]) x=y;
				else if (x[0]==y[0]) x+={0, y[1]};
			}
			if (x[0]==INT_MAX) continue;
			auto c=[&](ll idx) {
				return pre[idx]-pre[i]<=b[j];
			};
			int r=LASTTRUE(c, i, n);
			H u=x+makeH(m-j-1, 0);
			int lb=dp[j].lower_bound(u);
			int ub=dp[j].upper_bound(u);
			if (lb<=r) dp[j].add(max(lb, i+1), min(ub, r+1), {0, u[1]});
			if (ub<=r) dp[j].set(ub, r+1, u);
		}
	}
	H ans={INT_MAX, -1};
	FOR(m) {
		H x=dp[i].query(n, n+1);
		if (x[0]==INT_MAX) continue;
		if (ans[0]>x[0]) ans=x;
		else if (ans[0]==x[0]) ans+={0, x[1]};
	}
	if (ans[0]!=INT_MAX) print(ans[0], ans[1]);
	else print(-1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}
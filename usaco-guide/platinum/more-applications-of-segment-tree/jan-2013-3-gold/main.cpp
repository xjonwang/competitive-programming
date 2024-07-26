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

struct ST {
	int n, z; vt<int> seg, pref, suf, d;
	ST(int a) : n(1) {
		while (n<a) n*=2;
		z=__builtin_clz(n);
		seg=pref=suf=vt<int>(2*n, 0);
		d.assign(n, -1);
		FOR(a) seg[n+i]=pref[n+i]=suf[n+i]=1;
		FOR(i, 2*n-1, 1, -1) merge(i); 
	}
	int size(int i) {
		return 1<<(__builtin_clz(i)-z);
	}
	void apply(int i, int x) {
		seg[i]=pref[i]=suf[i]=size(i)*x;
		if (i<n) d[i]=x;
	}
	void merge(int i) {
		int h=size(i);
		int p=i>>1;
		if (d[p]==-1) {
			seg[p]=max(max(seg[i], seg[i^1]), suf[i&-2]+pref[i|1]);
			pref[p]=pref[i&-2]+(pref[i&-2]==h ? pref[i|1] : 0);
			suf[p]=suf[i|1]+(suf[i|1]==h ? suf[i&-2] : 0);
		} else {
			seg[p]=pref[p]=suf[p]=size(p)*d[p];
		}
	}
	void build(int i) {
		for (; i>1; i>>=1) merge(i);
	}
	void push(int i) {
		if (d[i]!=-1) {
			apply(i<<1, d[i]);
			apply(i<<1|1, d[i]);
			d[i]=-1;
		}
	}
	void propagate(int i) {
		FOR(j, 32-z, 0, -1) {
			int p=i>>j;
			push(p);
		}
	}
	void modify(int l, int r, int x) {
		int l0=l+n, r0=r+n-1;
		propagate(l0);
		propagate(r0);
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) apply(l++, x);
			if (r&1) apply(--r, x);
		}
		build(l0);
		build(r0);
	}
	int query(int x) {
		if (seg[1]<x) return -1;
		int i=1;
		while (i<n) {
			push(i);
			int h=size(i), p=h*(i^(1<<(32-__builtin_clz(i)-1)));
			if (seg[i<<1]>=x) i<<=1;
			else if (suf[i<<1]+pref[i<<1|1]>=x) return p+h/2-suf[i<<1];
			else i<<=1, i|=1;
		}
		return i-n;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("seating.in", "r", stdin);
	freopen("seating.out", "w", stdout);
	int n, m; read(n, m);
	char q; int x, y, ans=0;
	ST st(n);
	FOR(m) {
		read(q);
		if (q=='A') {
			read(x);
			int t=st.query(x);
			if (t==-1) ans++;
			else st.modify(t, t+x, 0);
		} else {
			read(x, y); --x;
			st.modify(x, y, 1);
		}
	}
	print(ans);
}
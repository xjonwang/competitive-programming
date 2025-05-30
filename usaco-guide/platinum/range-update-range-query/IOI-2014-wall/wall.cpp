#include "wall.h"

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
	int n, h;
	vt<int> v, add, rem;
	ST(int a) : n(1) {
		while (n<a) n<<=1;
		h=32-__builtin_clz(n);
		add.asn(2*n, 0), rem.asn(2*n, INT_MAX), v.asn(2*n, 0);
	}	
	void apply_add(int i, int x) {
		if (i<n) {
			umax(rem[i], x);
			umax(add[i], x);
		} else {
			umax(v[i], x);
		}
	}
	void apply_rem(int i, int x) {
		if (i<n) {
			umin(add[i], x);
			umin(rem[i], x);
		} else {
			umin(v[i], x);
		}
	}
	void push(int i) {
		if (add[i]>0) {
			apply_add(i<<1, add[i]);
			apply_add(i<<1|1, add[i]);
			add[i]=0;
		}
		if (rem[i]<INT_MAX) {
			apply_rem(i<<1, rem[i]);
			apply_rem(i<<1|1, rem[i]);
			rem[i]=INT_MAX;
		}
	}
	void propagate(int i) {
		FOR(j, h-1, 0, -1) {
			push(i>>j);
		}
	}	
	void set_add(int l, int r, int x) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		propagate(l0), propagate(r0);
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) apply_add(l++, x);
			if (r&1) apply_add(--r, x);
		}
	}
	void set_rem(int l, int r, int x) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		propagate(l0), propagate(r0);
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) apply_rem(l++, x);
			if (r&1) apply_rem(--r, x);
		}
	}
	int query(int i) {
		i+=n;
		propagate(i);
		return v[i];
	}
};

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	ST st(n);
	FOR(k) {
		switch (op[i]) {
			case 1:
				st.set_add(left[i], right[i]+1, height[i]);	
				break;
			case 2:
				st.set_rem(left[i], right[i]+1, height[i]);
				break;
		}
	}
	FOR(n) finalHeight[i]=st.query(i);
}
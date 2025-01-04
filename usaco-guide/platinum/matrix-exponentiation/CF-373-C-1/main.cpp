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

struct mat {
	ll a, b, c, d;
	mat(ll a, ll b, ll c, ll d) : a(a), b(b), c(c), d(d) {};
	ll &operator()(int row, int col) {
		switch (row) {
		case 0:
			switch (col) {
			case 0:
				return a;
			case 1:
				return b;
			}
			break;
		case 1:
			switch (col) {
			case 0:
				return c;
			case 1:
				return d;
			}
			break;
		}
		return a;
	}
	mat operator+(const mat &o) {
		return mat((a+o.a)%MOD, (b+o.b)%MOD, (c+o.c)%MOD, (d+o.d)%MOD);
	}
	mat &operator+=(const mat &o) {
		a=(a+o.a)%MOD;
		b=(b+o.b)%MOD;
		c=(c+o.c)%MOD;
		d=(d+o.d)%MOD;
		return *this;
	}
	mat operator*(const mat &o) {
		return mat((a*o.a+b*o.c)%MOD, (a*o.b+b*o.d)%MOD, (c*o.a+d*o.c)%MOD, (c*o.b+d*o.d)%MOD);
	}
	mat &operator*=(const mat &o) {
		*this=*this*o;
		return *this;
	}
	bool operator==(const mat &o) {
		return a==o.a&&b==o.b&&c==o.c&&d==o.d;
	}
	bool operator!=(const mat &o) {
		return !(*this==o);
	}
};

const mat IDENTITY(1, 0, 0, 1);
const mat ZERO(0, 0, 0, 0);
const mat FAC(1, 1, 1, 0);

mat matexp(mat m, int e) {
	mat ret(IDENTITY);
	FOR(30) {
		if (e&(1<<i)) ret*=m;
		m*=m;
	}
	return ret;
}

struct ST {
	int n, h;
	vt<mat> v, d;
	ST(int n) : n(n), h(32-__builtin_clz(n)), v(2*n, IDENTITY), d(n, IDENTITY) {};
	void apply(int i, mat x) {
		v[i]*=x;
		if (i<n) d[i]*=x;
	}
	void build(int i) {
		for (; i>>=1;) v[i]=d[i]*(v[i<<1]+v[i<<1|1]);
	}
	void propagate(int i) {
		FOR(j, h-1, 0, -1) {
			int t=i>>j;
			if (d[t]!=IDENTITY) {
				apply(t<<1, d[t]);
				apply(t<<1|1, d[t]);
				d[t]=IDENTITY;
			}
		}
	}
	void modify(int l, int r, mat x) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) apply(l++, x);
			if (r&1) apply(--r, x);
		}
		build(l0);
		build(r0);
	}
	mat query(int l, int r) {
		l+=n, r+=n;
		propagate(l);
		propagate(r-1);
		mat ret(ZERO);
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) ret+=v[l++];
			if (r&1) ret+=v[--r];
		}
		return ret;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, x, y, z; read(n, m);
	ST st(n);
	FOR(n) {
		read(x);
		st.modify(i, i+1, matexp(FAC, --x));
	}
	FOR(m) {
		read(x);
		switch (x) {
		case 1:
			read(x, y, z);
			st.modify(--x, y, matexp(FAC, z));
			break;
		case 2:
			read(x, y);
			print(st.query(--x, y)(0, 0));
			break;
		}
	}
}
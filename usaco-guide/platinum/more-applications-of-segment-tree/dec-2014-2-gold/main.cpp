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

struct BIT {
	int n; vt<int> v;
	BIT(vt<int>& a) : n(sz(a)), v(a) {
		FOR(n) if ((i|(i+1))<n) v[i|(i+1)]+=v[i]; 
	}
	void modify(int i, int x) {
		for (; i<n; i|=i+1) v[i]+=x;
	}
	int query(int i) {
		int ret=0;
		for (; i>0; i&=i-1) ret+=v[i-1];
		return ret;
	}
	int query(int l, int r) {
		return query(r)-query(l);
	}
};

struct ST {
	int n; vt<int> v;
	ST(vt<int>& a) : n(sz(a)), v(2*n) {
		FOR(n) v[n+i]=a[i];
		FOR(i, n-1, 0, -1) v[i]=max(v[i<<1], v[i<<1|1]);
	}
	void modify(int i, int x) {
		for (v[i+=n]=x; i>1; i>>=1) v[i>>1]=max(v[i], v[i^1]);
	}
	int query(int l, int r) {
		int ret=0;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) ret=max(ret, v[l++]);
			if (r&1) ret=max(ret, v[--r]);
		}
		return ret;
	}
};

int dist(pii& a, pii& b) {
	return abs(a.f-b.f)+abs(a.s-b.s);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("marathon.in", "r", stdin);
	freopen("marathon.out", "w", stdout);
	int n, q, x, y, z; read(n, q);
	vt<pii> v(n); read(v);
	vt<int> d(n), t(n); d[n-1]=t[0]=t[n-1]=0;
	FOR(n-1) d[i]=dist(v[i], v[i+1]);
	FOR(i, 1, n-1) t[i]=d[i-1]+d[i]-dist(v[i-1], v[i+1]);
	ST st(t);
	BIT bit(d);
	char a;
	FOR(q) {
		read(a);
		switch (a) {
			case 'Q':
				read(x, y); --x, --y;
				print(bit.query(x, y)-st.query(x+1, y));
				break;
			case 'U':
				read(x, y, z); --x;
				v[x]={y, z};
				if (x>0) bit.modify(x-1, dist(v[x-1], v[x])-d[x-1]), d[x-1]=dist(v[x-1], v[x]);
				if (x<n-1) bit.modify(x, dist(v[x], v[x+1])-d[x]), d[x]=dist(v[x], v[x+1]);
				if (x>0 && x<n-1) st.modify(x, d[x-1]+d[x]-dist(v[x-1], v[x+1]));
				if (x>1) st.modify(x-1, d[x-2]+d[x-1]-dist(v[x-2], v[x]));
				if (x<n-2) st.modify(x+1, d[x]+d[x+1]-dist(v[x], v[x+2]));
				break;
		}
	}
}
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
	int n;
	vt<ll> c, v;
	ST(int n) : n(n), c(2*n, 0), v(2*n, 0) {};
	void add(int i) {
		for (i+=n, c[i]++, v[i]+=i-n; i>>=1; ) c[i]=c[i<<1]+c[i<<1|1], v[i]=v[i<<1]+v[i<<1|1];
	}
	void sub(int i) {
		for (i+=n, c[i]--, v[i]-=i-n; i>>=1; ) c[i]=c[i<<1]+c[i<<1|1], v[i]=v[i<<1]+v[i<<1|1];
	}
	ll qc(int l, int r) {
		ll ret=0;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) ret+=c[l++];
			if (r&1) ret+=c[--r];
		}
		return ret;
	}
	ll qv(int l, int r) {
		ll ret=0;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) ret+=v[l++];
			if (r&1) ret+=v[--r];
		}
		return ret;
	}
};

vt<int> za(string x) {
	int n=sz(x);
	vt<int> z(n, 0);
	int l=0, r=0;
	FOR(i, 1, n) {
		if (i<r) z[i]=min(r-i, z[i-l]);
		while (i+z[i]<n && x[z[i]]==x[i+z[i]]) z[i]++;
		if (umax(r, i+z[i])) l=i;
	}
	return z;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m; read(n, m);
	string a, b, cf; read(a, b, cf);
	reverse(all(b));
	string cr=cf;
	reverse(all(cr));
	vt<int> z1=za(cf.substr(0, m-1)+"#"+a), z2=za(cr.substr(0, m-1)+"#"+b);
	z1.erase(z1.begin(), z1.begin()+m), z2.erase(z2.begin(), z2.begin()+m);
	reverse(all(z2));
	ST st(m);
	ll ans=0;
	FOR(min(n, m-1)) st.add(z2[i]);
	FOR(n-m+1) {
		ans+=st.qv(m-z1[i], m)+(z1[i]-m+1)*st.qc(m-z1[i], m);
		st.add(z2[i+m-1]);
		st.sub(z2[i]);
	}
	FOR(i, max(0, n-m+1), n) {
		ans+=st.qv(m-z1[i], m)+(z1[i]-m+1)*st.qc(m-z1[i], m);
		st.sub(z2[i]);
	}
	print(ans);
}

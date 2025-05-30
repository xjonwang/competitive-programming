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
	int n, h;
	vt<int> v, d;
	ST(int n) : n(n), h(32-__builtin_clz(n)), v(2*n, 0), d(n, 0) {}
	void apply_add(int i, int x) {
		v[i]+=x;
		if (i<n) d[i]+=x;
	}
	void push(int i) {
		if (d[i]) {
			apply_add(i<<1, d[i]);
			apply_add(i<<1|1, d[i]);
			d[i]=0;
		}
	}
	void propagate(int i) {
		FOR(j, h, 0, -1) {
			push(i>>j);	
		}
	}
	void build(int i) {
		for (; i>>=1;) {
			v[i]=min(v[i<<1], v[i<<1|1])+d[i];
		}
	}
	void add(int l, int r, int x) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		propagate(l0), propagate(r0);
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) apply_add(l++, x);
			if (r&1) apply_add(--r, x);
		}
		build(l0), build(r0);
	}
	void minify(int i, int x) {
		propagate(i+=n);
		if (umin(v[i], x)) {
			build(i);
		}
	}
	int query(int l, int r) {
		l+=n, r+=n;
		propagate(l), propagate(r-1);
		int ret=INT_MAX;
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) umin(ret, v[l++]);
			if (r&1) umin(ret, v[--r]);
		}
		return ret;
	}
};

struct spr {
	int x1, y1, x2, y2;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("boards.in", "r", stdin);
	freopen("boards.out", "w", stdout);
	int k, n; read(k, n);
	map<int, vt<spr>> v;
	vt<int> xridx, yridx;	
	FOR(n) {
		int x1, y1, x2, y2;
		read(x1, y1, x2, y2);
		xridx.pb(x1), xridx.pb(x2);
		yridx.pb(y1), yridx.pb(y2);
		v[x1].pb({x1, y1, x2, y2});
	}
	sort(all(xridx));
	xridx.erase(unique(all(xridx)), xridx.end());
	sort(all(yridx));
	yridx.erase(unique(all(yridx)), yridx.end());
	int mx=sz(xridx), my=sz(yridx);
	map<int, int> yidx;
	FOR(my) yidx[yridx[i]]=i;
	ST st(my);
	map<int, vt<pii>> dest;
	int p=0;
	EACH(x, xridx) {
		st.add(0, my, x-p);
		auto& sp=v[x];
		sort(all(sp), [](const spr& a, const spr& b) { return a.y1<b.y1; });
		for (auto &[_, y1, x2, y2] : sp) {
			for (auto &[y, d] : dest[x]) st.minify(y, d);
			dest[x].clear();
			int d=st.query(0, yidx[y1]+1)+y1;
			assert(d>=0);
			dest[x2].pb({yidx[y2], d-y2});
		}
		for (auto &[y, d] : dest[x]) st.minify(y, d);
		dest[x].clear();
		p=x;
	}
	st.add(0, my, k-p);
	print(st.query(0, my)+k);
}
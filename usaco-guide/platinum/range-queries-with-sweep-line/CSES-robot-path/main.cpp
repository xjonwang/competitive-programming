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
	vt<int> v;
	ST(int n) : n(n), v(2*n) {}
	void set(int i, int x) {
		for (v[i+=n]=x; i>>=1;) {
			v[i]=min(v[i<<1], v[i<<1|1]);
		}
	}
	int query(int l, int r) {
		int ret=INT_MAX;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) umin(ret, v[l++]);
			if (r&1) umin(ret, v[--r]);
		}
		return ret;
	}
	int query(int l, int r, int x) {
		vt<int> vl, vr;
		int mx=INT_MAX;
		for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
			if (l&1) {
				umin(mx, v[l]);
				vl.pb(l);
				l++;
			}
			if (r&1) {
				--r;
				umin(mx, v[r]);
				vr.pb(r);
			}
		}
		if (mx>=x) return -1;
		reverse(all(vr));
		EACH(i, vl) if (v[i]<x) return walk(i, x);
		EACH(i, vr) if (v[i]<x) return walk(i, x);
		return -1;
	}
	int walk(int i, int x) {
		while (i<n) {
			if (v[i<<1]<x) i=i<<1;
			else i=i<<1|1;
		}
		return i-n;
	}
};

struct line {
	int x1, y1, x2, y2, i;
	line(int x1, int y1, int x2, int y2, int i) : x1(x1), y1(y1), x2(x2), y2(y2), i(i) {
		if (x1>x2) swap(x1, x2);
		if (y1>y2) swap(y1, y2);
	}
	void add(vt<vt<line>>& hori, vt<vt<line>>& vert1, vt<vt<line>>& vert2) {
		if (x1==x2) {
			vert1[y1].pb(*this);
			vert2[y2].pb(*this);
		} else {
			hori[y1].pb(*this);
		}
	}
};

pll mv(pll st, char c, int x) {
	switch (c) {
		case 'U':
			return {st.f, st.s+x};
		case 'D':
			return {st.f, st.s-x};
		case 'R':
			return {st.f+x, st.s};
		case 'L':
			return {st.f-x, st.s};
		default:
			assert(false);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; read(n);
	vt<pll> p(n+1); p[0]={0, 0};
	FOR(n) {
		char c; int x; read(c, x);
		p[i+1]=mv(p[i], c, x);
	}
	vt<ll> xridx, yridx;
	for (auto &[x, y] : p) xridx.pb(x), yridx.pb(y);
	sort(all(xridx)), sort(all(yridx));
	xridx.erase(unique(all(xridx)), xridx.end());
	yridx.erase(unique(all(yridx)), yridx.end());
	int mx=sz(xridx), my=sz(yridx);
	map<int, int> xidx, yidx;
	FOR(mx) xidx[xridx[i]]=i;
	FOR(my) yidx[yridx[i]]=i;
	vt<line> v;
	vt<vt<line>> hori(my), vert1(my), vert2(my);
	FOR(n) {
		auto &[x1, y1]=p[i];
		auto &[x2, y2]=p[i+1];
		v.eb(xidx[x1], yidx[y1], xidx[x2], yidx[y2], i);
		v.back().add(hori, vert1, vert2);
	}
	vt<deque<int>> win(mx);
	ST st(mx);
	pii inter={INT_MAX, INT_MAX};
	FOR(my) {
		EACH(li, vert1[i]) {
			while (sz(win[li.x1]) && win[mx].back()>li.i) win[li.x1].pop_back();
			win[li.x1].push_back(li.i);
			st.set(li.x1, win[li.x1].front());	
		}
		EACH(li, hori[i]) {
			int u=st.query(li.x1, li.x2+1, li.i);
			if (u!=-1) umin(inter, {i, u});
			else if ((u=st.query(li.x1, li.x2+1))!=INT_MAX) umin(inter, {u, i});
		}
		EACH(li, vert2[i]) {
			if (win[li.x1].front()==li.i) win[li.x1].pop_front();
			if (sz(win[li.x1])) st.set(li.x1, win[li.x1].front());	
			else st.set(li.x1, INT_MAX);	
		}
	}
	print(inter.f, inter.s);
}

/*
5
U 2
R 3
D 1
L 5
U 2
*/
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

struct RUPS {
	vt<ll> v;
	RUPS(int n) : v(n) {}
	RUPS(vt<ll>& va) : v(sz(va)) {
		v[0]+=va[0], v[1]+=v[0];
		FOR(i, 1, sz(va)) {
			v[i]+=va[i]-va[i-1];
			int r=i|(i+1);
			if (r<sz(v)) v[r]+=v[i];
		}
	}
	void update(int pos, ll dif) {
		for (; pos < sz(v); pos |= pos + 1) v[pos] += dif;
	}
	void range_update(int l, int r, ll dif) {
		update(l, dif);
		update(r, -dif);
	}
	ll query(int pos) {
		ll res = 0;
		for (++pos; pos > 0; pos &= pos - 1) res += v[pos-1];
		return res;
	}
};

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi; ll mset = LLONG_MIN, madd = 0, val = LLONG_MAX;
	Node(int lo,int hi):lo(lo),hi(hi){}
	Node(vt<ll>& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = min(l->val, r->val);
		}
		else val = v[lo];
	}
	ll query(int L, int R) {
		if (R <= lo || hi <= L) return LLONG_MAX;
		if (L <= lo && hi <= R) return val;
		push();
		return min(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void add(int L, int R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != LLONG_MIN) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = min(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != LLONG_MIN)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = LLONG_MIN;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

struct edge {
	int u, v, w;
};

vt<edge> e;
vt<vt<pii>> adj;
vt<int> ti, to, r;
vt<ll> dist;
int t;

void dfs(int v, ll d, int p=-1) {
	dist[t]=d;
	ti[v]=t++;
	for (auto& [u, c] : adj[v]) if (u!=p) dfs(u, d+c, v);
	to[v]=t;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, q, x, y, z; read(n, q);
	e.resize(2*n-2), adj.resize(n), ti.resize(n), to.resize(n), r.resize(n), dist.resize(n);
	FOR(n-1) {
		read(x, y, z); --x, --y;
		e[i]={x, y, z};
		adj[x].pb({y, z});
		adj[y].pb({x, z});
	}
	FOR(i, 1, n) {
		read(x, y, z); --x, --y;
		e[n-2+i]={x, y, z};
		r[x]=z;
	}
	dfs(0, 0);
	RUPS rups(dist);
	FOR(i, 1, n) dist[ti[i]]+=r[i];
	Node *lst = new Node(dist, 0, n);
	auto anc=[&](int u, int v) { return ti[u]<=ti[v] && to[u]>=to[v]; };
	FOR(q) {
		read(x);
		if (x==1) {
			read(x, y); --x;
			auto [u, v, w]=e[x];
			if (x<n-1) {
				u=ti[u]>ti[v] ? u : v;
				rups.range_update(ti[u], to[u], y-w);
				lst->add(ti[u], to[u], y-w);
			} else {
				lst->add(ti[u], ti[u]+1, y-w);
			}
			e[x].w=y;
		} else {
			read(x, y); --x, --y;
			if (anc(x, y)) print(rups.query(ti[y])-rups.query(ti[x]));
			else print(lst->query(ti[x], to[x])-rups.query(ti[x])+rups.query(ti[y]));
		}
	}
}
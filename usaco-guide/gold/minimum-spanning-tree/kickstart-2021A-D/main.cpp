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

struct node {
	int dir, idx, w;
};
struct node_cmp {
	bool operator()(const node& a, const node& b) const {
		return a.w>b.w;
	}
};

struct point {
	int r, c, w;
};
struct point_cmp {
	bool operator()(const point& a, const point& b) const {
		return a.w!=b.w ? a.w<b.w : (a.r!=b.r ? a.r<b.r : a.c<b.c);
	}
};

int solve() {
	int n; read(n);
	vt<vt<int>> a(n, vt<int>(n)), b(n, vt<int>(n)); read(a, b);
	vt<int> t1(n), t2(n); read(t1, t2);
	vt<vt<bool>> vis(2, vt<bool>(n, 0));
	vt<vt<int>> cost(2, vt<int>(n, 0));
	vt<vt<set<point, point_cmp>>> pts(2, vt<set<point, point_cmp>>(n));
	priority_queue<node, vt<node>, node_cmp> pq;
	FOR(n) {
		FOR(j, n) {
			if (a[i][j]==-1) {
				pts[0][j].insert({i, j, b[i][j]});
				pts[1][i].insert({i, j, b[i][j]});
			}
		}
	}
	FOR(dir, 2) {
		FOR(idx, n) {
			for (auto it=pts[dir][idx].begin(); it!=pts[dir][idx].end() && it!=prev(pts[dir][idx].end()); it++) {
				cost[dir][idx]+=it->w;
			}
		}
	}
	FOR(dir, 2) FOR(idx, n) pq.push({dir, idx, cost[dir][idx]});
	auto upd=[&](int dir, int idx, point p) {
		auto it=pts[dir][idx].find(p);
		if (it==pts[dir][idx].end()) {
			return;
		} else if (next(it)==pts[dir][idx].end()) {
			if (it!=pts[dir][idx].begin()) cost[dir][idx]-=prev(it)->w;
		} else {
			cost[dir][idx]-=it->w;
		}
		pts[dir][idx].erase(it);
		pq.push({dir, idx, cost[dir][idx]});
	};
	int ans=0;
	while (sz(pq)) {
		auto [dir, idx, w]=pq.top(); pq.pop();
		if (vis[dir][idx]) continue;
		vis[dir][idx]=1;
		ans+=w;
		switch (dir) {
			case 0:
				for (auto &[r, c, w] : pts[0][idx]) upd(1, r, {r, c, w});
				break;
			case 1:
				for (auto &[r, c, w] : pts[1][idx]) upd(0, c, {r, c, w});
				break;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen("test_set_1/ts1_input.txt", "r", stdin);
	freopen("out.out", "w", stdout);
	int t; read(t);
	FOR(t) cout << "Case #" << i+1 << ": " << solve() << endl; 
}
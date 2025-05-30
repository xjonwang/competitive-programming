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

ll dist(pii x, pii y) {
	return abs(y.f-x.f)+abs(y.s-x.s);
}

struct edge {
	int u, v;
	pii p1, p2;
	ll d;
	edge(int u, int v, pii p1, pii p2) : u(u), v(v), p1(p1), p2(p2), d(dist(p1, p2)) {}
};

struct dee {
	int x1, y1, x2, y2, idx, pre;
	vt<int> north, south, east, west;
	map<pii, int> id;
	dee(int x1, int y1, int x2, int y2, int idx) : x1(x1), y1(y1), x2(x2), y2(y2), idx(idx),
		north({x1, x2}), south({x1, x2}), east({y1, y2}), west({y1, y2})
	{
		if (x1!=x2 && y1!=y2) {
			id[{x1, y1}]=0;
			id[{x1, y2}]=1;
			id[{x2, y1}]=2;
			id[{x2, y2}]=3;
		} else {
			id[{x1, y1}]=0;
		}
	}
	void add(int dir, int pos) {
		switch (dir) {
			case 0:
				north.pb(pos);	
				if (!id.count({pos, y2})) id[{pos, y2}]=sz(id);
				break;
			case 1:
				east.pb(pos);
				if (!id.count({x2, pos})) id[{x2, pos}]=sz(id);
				break;
			case 2:
				south.pb(pos);
				if (!id.count({pos, y1})) id[{pos, y1}]=sz(id);
				break;
			case 3:
				west.pb(pos);
				if (!id.count({x1, pos})) id[{x1, pos}]=sz(id);
				break;
		}
	}
	void process_interior_edges(vt<edge>& e) {
		sort(all(north));
		sort(all(south));
		sort(all(east));
		sort(all(west));
		FOR(i, 1, sz(north)) e.eb(idx, idx, make_pair(north[i-1], y2), make_pair(north[i], y2));
		FOR(i, 1, sz(south)) e.eb(idx, idx, make_pair(south[i-1], y1), make_pair(south[i], y1));
		FOR(i, 1, sz(east)) e.eb(idx, idx, make_pair(x2, east[i-1]), make_pair(x2, east[i]));
		FOR(i, 1, sz(west)) e.eb(idx, idx, make_pair(x1, west[i-1]), make_pair(x1, west[i]));
	}
	int get_id(pii x) {
		if (!id.count(x)) assert(false);
		return pre+id[x];
	}
};

void solve() {
	int x1, y1, x2, y2;
	vt<dee> v;
	read(x1, y1, x2, y2);
	v.eb(x1, y1, x1, y1, sz(v));
	v.eb(x2, y2, x2, y2, sz(v));
	int n; read(n);
	FOR(n) {
		read(x1, y1, x2, y2);
		if (x1>x2) swap(x1, x2);
		if (y1>y2) swap(y1, y2);
		v.eb(x1, y1, x2, y2, sz(v));
	}
	int sx, sy;
	sort(all(v), [](const dee& a, const dee& b) { return a.y1>b.y1; });
	vt<edge> e;
	FOR(n+2) {
		sy=v[i].y1;
		sx=v[i].x1;
		FOR(j, i+1, n+2) {
			if (v[j].y2<=sy && v[j].x1<=sx && v[j].x2>=sx) {
				v[j].add(0, sx);
				e.eb(v[i].idx, v[j].idx, make_pair(sx, sy), make_pair(sx, v[j].y2));
				break;
			}
		}
		sx=v[i].x2;
		FOR(j, i+1, n+2) {
			if (v[j].y2<=sy && v[j].x1<=sx && v[j].x2>=sx) {
				v[j].add(0, sx);
				e.eb(v[i].idx, v[j].idx, make_pair(sx, sy), make_pair(sx, v[j].y2));
				break;
			}
		}
	}
	sort(all(v), [](const dee& a, const dee& b) { return a.y1<b.y1; });
	FOR(n+2) {
		sy=v[i].y2;
		sx=v[i].x1;
		FOR(j, i+1, n+2) {
			if (v[j].y1>=sy && v[j].x1<=sx && v[j].x2>=sx) {
				v[j].add(2, sx);
				e.eb(v[i].idx, v[j].idx, make_pair(sx, sy), make_pair(sx, v[j].y1));
				break;
			}
		}
		sx=v[i].x2;
		FOR(j, i+1, n+2) {
			if (v[j].y1>=sy && v[j].x1<=sx && v[j].x2>=sx) {
				v[j].add(2, sx);
				e.eb(v[i].idx, v[j].idx, make_pair(sx, sy), make_pair(sx, v[j].y1));
				break;
			}
		}
	}
	sort(all(v), [](const dee& a, const dee& b) { return a.x1>b.x1; });
	FOR(n+2) {
		sx=v[i].x1;
		sy=v[i].y1;
		FOR(j, i+1, n+2) {
			if (v[j].x2<=sx && v[j].y1<=sy && v[j].y2>=sy) {
				v[j].add(1, sy);
				e.eb(v[i].idx, v[j].idx, make_pair(sx, sy), make_pair(v[j].x2, sy));
				break;
			}
		}
		sy=v[i].y2;
		FOR(j, i+1, n+2) {
			if (v[j].x2<=sx && v[j].y1<=sy && v[j].y2>=sy) {
				v[j].add(1, sy);
				e.eb(v[i].idx, v[j].idx, make_pair(sx, sy), make_pair(v[j].x2, sy));
				break;
			}
		}
	}
	sort(all(v), [](const dee& a, const dee& b) { return a.x1<b.x1; });
	FOR(n+2) {
		sx=v[i].x2;
		sy=v[i].y1;
		FOR(j, i+1, n+2) {
			if (v[j].x1>=sx && v[j].y1<=sy && v[j].y2>=sy) {
				v[j].add(3, sy);
				e.eb(v[i].idx, v[j].idx, make_pair(sx, sy), make_pair(v[j].x1, sy));
				break;
			}
		}
		sy=v[i].y2;
		FOR(j, i+1, n+2) {
			if (v[j].x1>=sx && v[j].y1<=sy && v[j].y2>=sy) {
				v[j].add(3, sy);
				e.eb(v[i].idx, v[j].idx, make_pair(sx, sy), make_pair(v[j].x1, sy));
				break;
			}
		}
	}
	FOR(n+2) v[i].process_interior_edges(e);
	sort(all(v), [](const dee& a, const dee& b) { return a.idx<b.idx; });
	v[0].pre=0;
	FOR(i, 1, n+2) v[i].pre=v[i-1].pre+sz(v[i-1].id);
	n=v[n+1].pre+sz(v[n+1].id);
	vt<vt<pair<int, ll>>> adj(n);
	for (auto &[i1, i2, p1, p2, d] : e) {
		int idx1=v[i1].get_id(p1), idx2=v[i2].get_id(p2);
		if (idx1==idx2) continue;
		adj[idx1].eb(idx2, d);
		adj[idx2].eb(idx1, d);
	}
	vt<ll> dist(n, LLONG_MAX);
	priority_queue<pair<int, ll>, vt<pair<int, ll>>, greater<pair<int, ll>>> pq;
	dist[0]=0, pq.push({0, 0});
	while (sz(pq)) {
		auto [v, d]=pq.top(); pq.pop();
		if (d>dist[v]) continue;
		for (auto& [u, w] : adj[v]) if (umin(dist[u], d+w)) pq.push({u, d+w});
	}
	print(dist[1]!=LLONG_MAX ? to_string(dist[1]) : "No Path");
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}
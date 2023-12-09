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

int dr[4]={1, -1, 0, 0}, dc[4]={0, 0, 1, -1};

int n, k, m1, m2, d1, d2;
vt<vt<int>> bd;
vt<vt<char>> g;

bool check(int x) {
	if (x>=bd[m1][m2]) return false;
	vt<vt<int>> dist(n, vt<int>(n, -1));
	queue<pii> q;
	dist[m1][m2]=0, q.push({m1, m2});
	while (sz(q)) {
		pii v=q.front(); q.pop();
		FOR(4) {
			int r=v.f+dr[i], c=v.s+dc[i];
			if (r>=0 && r<n && c>=0 && c<n && g[r][c]!='T' && dist[r][c]==-1 && (dist[v.f][v.s]+1)/k+x<bd[r][c]) {
				if (r==d1 && c==d2) return true;
				dist[r][c]=dist[v.f][v.s]+1;
				q.push({r, c});
			}
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, k);
	g.assign(n, vt<char>(n)), bd.assign(n, vt<int>(n, -1));
	vt<pii> h;
	char x;
	FOR(n) {
		FOR(j, n) {
			read(x);
			g[i][j]=x;
			if (x=='M') m1=i, m2=j;
			else if (x=='D') d1=i, d2=j;
			else if (x=='H') h.pb({i, j});
		}
	}
	queue<pii> q;
	EACH(p, h) bd[p.f][p.s]=0, q.push({p.f, p.s});
	while (sz(q)) {
		pii v=q.front(); q.pop();
		FOR(4) {
			int r=v.f+dr[i], c=v.s+dc[i];
			if (r>=0 && r<n && c>=0 && c<n && g[r][c]!='T' && g[r][c]!='D' && bd[r][c]==-1) {
				bd[r][c]=bd[v.f][v.s]+1;
				q.push({r, c});
			}
		}
	}
	bd[d1][d2]=INT_MAX;
	int l=-1, r=1e6;
	for (int i=r-l; i>0; i/=2) while (l+i<=r && check(l+i)) l+=i;
	print(l);
}
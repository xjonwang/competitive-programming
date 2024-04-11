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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, d; read(n, d);
	vt<vt<char>> v(n, vt<char>(n));
	char x;
	vt<pii> b, st;
	FOR(n) {
		FOR(j, n) {
			read(x);
			if (x=='#') b.pb({i, j});
			else if (x=='S') st.pb({i, j});
		}
	}
	vt<vt<int>> bd(n, vt<int>(n, INT_MAX));
	queue<pii> q;
	EACH(p, b) bd[p.f][p.s]=0, q.push(p);
	while (sz(q)) {
		auto [pr, pc]=q.front(); q.pop();
		FOR(4) {
			int r=pr+dr[i], c=pc+dc[i];
			if (r>=0 && r<n && c>=0 && c<n && bd[r][c]==INT_MAX) {
				bd[r][c]=bd[pr][pc]+1;
				q.push({r, c});
			}
		}
	}
	vt<vt<int>> rd(n, vt<int>(n, INT_MAX));
	vt<vt<pii>> rp(n/2); rp[0]=st;
	EACH(p, st) rd[p.f][p.s]=0, q.push(p);
	while (sz(q)) {
		auto [pr, pc]=q.front(); q.pop();
		FOR(4) {
			int r=pr+dr[i], c=pc+dc[i];
			if (r>=0 && r<n && c>=0 && c<n && rd[r][c]==INT_MAX && rd[pr][pc]/d<bd[r][c]) {
				rp[min(bd[r][c]-1, rd[r][c]/d)].pb({r, c});
				rd[r][c]=rd[pr][pc]+1;
				if (rd[r][c]/d<bd[r][c]) q.push({r, c});
			}
		}
	}
	vt<vt<int>> dist(n, vt<int>(n, INT_MAX));
	int l;
	FOR(i, n/2-1, -1, -1) {
		if (sz(rp[i])) {
			EACH(p, rp[i]) dist[p.f][p.s]=-i, q.push(p);
			l=i;
			break;
		}
	}
	while (sz(q)) {
		auto [pr, pc]=q.front(); q.pop();
		if (-dist[pr][pc]<l) {
			--l;
			EACH(p, rp[l]) dist[p.f][p.s]=-l, q.push(p);
		}
		if (dist[pr][pc]==0) break;
		FOR(4) {
			int r=pr+dr[i], c=pc+dc[i];
			if (r>=0 && r<n && c>=0 && c<n && dist[r][c]==INT_MAX) {
				dist[r][c]=dist[pr][pc]+1;
				q.push({r, c});
			}
		}
	}
	int ans=0;
	FOR(n) FOR(j, n) ans+=dist[i][j]<=0;
	print(ans);
}
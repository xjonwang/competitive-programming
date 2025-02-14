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
	int r, c, w;
};

int n, m, w;
vt<node> fo;
vt<vt<char>> v;

int adj[13][13], dr[4]={1, -1, 0, 0}, dc[4]={0, 0, 1, -1}, dp[1<<12], sdp[1<<12], tdp[1<<12][12];

void flood(int str, int stc, int idx) {
	vt<vt<int>> d(n, vt<int>(n, -1)); 
	deque<pii> q;
	d[str][stc]=0; q.push_front({str, stc});
	while (sz(q)) {
		auto [pr, pc]=q.front(); q.pop_front();
		FOR(4) {
			int r=pr+dr[i], c=pc+dc[i];
			if (r<0 || r>=n || c<0 || c>=n || d[r][c]!=-1) continue;
			if (v[r][c]=='.') d[r][c]=d[pr][pc], q.push_front({r, c});
			else if (v[r][c]=='+') d[r][c]=d[pr][pc]+1, q.push_back({r, c});
		}
	}
	FOR(m+1) adj[idx][i]=d[fo[i].r][fo[i].c];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, m, w);
	v.assign(n, vt<char>(n)); read(v);
	int x, y, z; fo.resize(m+1);
	FOR(m) {
		read(x, y, z); --x, --y;
		fo[i]={x, y, z};
	}	
	fo[m]={0, 0, 0};
	FOR(m+1) flood(fo[i].r, fo[i].c, i);
	FOR(i, 1, 1<<m) {
		ll t=0;
		FOR(j, m) {
			tdp[i][j]=1e6;
			if (i&(1<<j)) t+=fo[j].w;
		}
		sdp[i]=1e6;
		if (t>w) continue;
		FOR(j, m) {
			if (i&(1<<j)) {
				int b=i^(1<<j);
				if (b) {
					FOR(k, m) {
						if (b&(1<<k)) {
							umin(tdp[i][j], tdp[b][k]+adj[k][j]);
						}
					}
				} else {
					umin(tdp[i][j], adj[m][j]);
				}
			}
		} 
		FOR(j, m) if (i&(1<<j)) umin(sdp[i], tdp[i][j]+adj[j][m]);
	}
	FOR(i, 1, 1<<m) {
		dp[i]=1e6;
		int b=0;
		do {
			umin(dp[i], dp[b]+sdp[i^b]);
		} while (b=(b-i)&i);
	}
	print(dp[(1<<m)-1]);
}
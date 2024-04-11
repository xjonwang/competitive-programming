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

ll dist(ll x1, ll y1, ll x2, ll y2) {
	return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}

const int N = 31;
ll dp[N][N*N][N][N];
int cost[N][N][N][3];
vt<int> pos[3];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	string s; int m; read(s, m);
	dp[0][0][0][0]=1;
	int n=sz(s);
	FOR(n) {
		switch (s[i]) {
			case 'K':
				pos[0].pb(i);
				break;
			case 'E':
				pos[1].pb(i);
				break;
			default:
				pos[2].pb(i);
				break;
		}
	}
	FOR(sz(pos[0])+1) {
		FOR (j, sz(pos[1])+1) {
			FOR(k, sz(pos[2])+1) {
				vt<int> pre(n, 0);
				FOR(h, i) pre[pos[0][h]]++;
				FOR(h, j) pre[pos[1][h]]++;
				FOR(h, k) pre[pos[2][h]]++;
				FOR(h, 1, n) pre[h]+=pre[h-1];
				if (i<sz(pos[0])) cost[i][j][k][0]=pos[0][i]-pre[pos[0][i]];
				if (j<sz(pos[1])) cost[i][j][k][1]=pos[1][j]-pre[pos[1][j]];
				if (k<sz(pos[2])) cost[i][j][k][2]=pos[2][k]-pre[pos[2][k]];
			}
		}
	}
	FOR(n) {
		FOR(j, n*n) {
			FOR(k, sz(pos[0])+1) {
				FOR(h, sz(pos[1])+1) {
					if (k<sz(pos[0]) && j+cost[k][h][i-k-h][0]<n*n) dp[i+1][j+cost[k][h][i-k-h][0]][k+1][h]+=dp[i][j][k][h];
					if (h<sz(pos[1]) && j+cost[k][h][i-k-h][1]<n*n) dp[i+1][j+cost[k][h][i-k-h][1]][k][h+1]+=dp[i][j][k][h];
					if (j+cost[k][h][i-k-h][2]<n*n) dp[i+1][j+cost[k][h][i-k-h][2]][k][h]+=dp[i][j][k][h];
				}
			}
		}
	}
	ll ans=0;
	FOR(min(n*n, m+1)) ans+=dp[n][i][sz(pos[0])][sz(pos[1])];
	print(ans);
}
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

int f[10][4]={{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {2, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 1}, {3, 0, 0, 0}, {0, 2, 0, 0}};

ll (* solve(ll x))[55][37][19][19] {
	vt<int> v;
	while (x) v.pb(x%10), x/=10;
	int n=sz(v);
	ll (*dp)[55][37][19][19] = new ll[2][55][37][19][19];
	memset(dp, -1, 2 * 55 * 37 * 19 * 19 * sizeof(ll));
	dp[0][0][0][0][0]=dp[1][0][0][0][0]=0;
	ll e=1;
	FOR(n) {
		ll (*t)[55][37][19][19] = new ll[2][55][37][19][19];
		memset(t, -1, 2 * 55 * 37 * 19 * 19 * sizeof(ll));
		FOR(j, 2) {
			FOR(a, 55) {
				FOR(b, 37) {
					FOR(c, 19) {
						FOR(d, 19) {
							if (j) {
								FOR(k, i==n-1 ? 0 : 1, v[i]) {
									int na=a-f[k][0], nb=b-f[k][1], nc=c-f[k][2], nd=d-f[k][3];
									if (na>=0 && nb>=0 && nc>=0 && nd>=0 && dp[0][na][nb][nc][nd]>=0) umax(t[j][a][b][c][d], k*e+dp[0][na][nb][nc][nd]);
								}
								if (v[i]>0) {
									int na=a-f[v[i]][0], nb=b-f[v[i]][1], nc=c-f[v[i]][2], nd=d-f[v[i]][3];
									if (na>=0 && nb>=0 && nc>=0 && nd>=0 && dp[1][na][nb][nc][nd]>=0) umax(t[j][a][b][c][d], v[i]*e+dp[1][na][nb][nc][nd]);
								}
							} else {
								FOR(k, 1, 10) {
									int na=a-f[k][0], nb=b-f[k][1], nc=c-f[k][2], nd=d-f[k][3];
									if (na>=0 && nb>=0 && nc>=0 && nd>=0 && dp[0][na][nb][nc][nd]>=0) umax(t[j][a][b][c][d], k*e+dp[0][na][nb][nc][nd]);
								}
							}
						}
					}
				}
			}
		}
		e*=10;
		delete[] dp;
		dp=t;
	}
	return dp;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll a, b; read(a, b); a--;
	ll (*dp1)[55][37][19][19]=solve(b);
	ll (*dp2)[55][37][19][19]=solve(a);
	ll ea[55], eb[37], ec[19], ed[19];
	ea[0]=eb[0]=ec[0]=ed[0]=1;
	FOR(i, 1, 55) ea[i]=ea[i-1]*2;
	FOR(i, 1, 37) eb[i]=eb[i-1]*3;
	FOR(i, 1, 19) ec[i]=ec[i-1]*5;
	FOR(i, 1, 19) ed[i]=ed[i-1]*7;
	ll ans=b, m=1;
	FOR(a, 55) {
		FOR(b, 37) {
			FOR(c, 19) {
				FOR(d, 19) {
					if (ea[a]*eb[b]*ec[c]*ed[d]>m && dp1[1][a][b][c][d]>dp2[1][a][b][c][d]) {
						m=ea[a]*eb[b]*ec[c]*ed[d];
						ans=dp1[1][a][b][c][d];
					}
				}
			}
		}
	}
	delete[] dp1, dp2;
	print(ans);
}
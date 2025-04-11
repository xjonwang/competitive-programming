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

#define MAXD 39
ll dp[MAXD][3][2];

bool parity(int a, int b, int c) {
	return (a%3)%2 == ((a+b+c)%3)%2;
}

bool parity(ll a, int b) {
	a+=b;
	while (a) {
		if ((a%3)%2) return false;
		a/=3;
	}
	return true;
}

void solve(const vt<int>& digits, const vt<int>& difference) {
	FOR(3) {
		if (i>digits[0]) {
			if (parity(i, difference[0], 0)) {
				if (i+difference[0]>=3) dp[0][2][1]++;
				else dp[0][2][0]++;
			}
		} else if (i<digits[0]) {
			if (parity(i, difference[0], 0)) {
				if (i+difference[0]>=3) dp[0][0][1]++;
				else dp[0][0][0]++;
			}
		} else {
			if (parity(i, difference[0], 0)) {
				if (i+difference[0]>=3) dp[0][1][1]++;
				else dp[0][1][0]++;
			}
		}
	}
	FOR(i, MAXD-1) {
		FOR(j, 3) {
			if (j>digits[i+1]) {
				FOR(h, 3) {
					if (parity(j, difference[i+1], 0)) {
						if (j+difference[i+1]>=3) dp[i+1][2][1]+=dp[i][h][0];
						else dp[i+1][2][0]+=dp[i][h][0];
					}
					if (parity(j, difference[i+1], 1)) {
						if (j+difference[i+1]+1>=3) dp[i+1][2][1]+=dp[i][h][1];
						else dp[i+1][2][0]+=dp[i][h][1];
					}
				}
			} else if (j<digits[i+1]) {
				FOR(h, 3) {
					if (parity(j, difference[i+1], 0)) {
						if (j+difference[i+1]>=3) dp[i+1][0][1]+=dp[i][h][0];
						else dp[i+1][0][0]+=dp[i][h][0];
					}
					if (parity(j, difference[i+1], 1)) {
						if (j+difference[i+1]+1>=3) dp[i+1][0][1]+=dp[i][h][1];
						else dp[i+1][0][0]+=dp[i][h][1];
					}
				}
			} else {
				FOR(h, 3) {
					if (parity(j, difference[i+1], 0)) {
						if (j+difference[i+1]>=3) dp[i+1][h][1]+=dp[i][h][0];
						else dp[i+1][h][0]+=dp[i][h][0];
					}
					if (parity(j, difference[i+1], 1)) {
						if (j+difference[i+1]+1>=3) dp[i+1][h][1]+=dp[i][h][1];
						else dp[i+1][h][0]+=dp[i][h][1];
					}
				}
			}
		}
	}
}

ll extract(int len, const vt<int>& difference) {
	ll ret=0, e=1;
	FOR(i, len, MAXD) ret+=e*difference[i], e*=3;
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; read(n);
	ll z, x, y, leftover;
	FOR(n) {
		read(z, x, y);
		if (x>y) swap(x, y);
		ll d=y-x;
		y=x+z+1;
		vt<int> dx(MAXD), dy(MAXD), dd(MAXD);
		FOR(j, MAXD) {
			dx[j]=x%3, x/=3;
			dy[j]=y%3, y/=3;
			dd[j]=d%3, d/=3;
		}
		int sza=MAXD, szb=MAXD, szd=MAXD;
		while (sza && dx[sza-1]==0) sza--;
		while (szb && dy[szb-1]==0) szb--;
		while (szd && dy[szd-1]==0) szd--;
		ll ans=0;
		if (sza>0) {
			memset(dp, 0, sizeof(dp));
			solve(dx, dd);
			leftover=extract(sza, dd);
			if (parity(leftover, 0)) ans-=dp[sza-1][0][0];
			if (parity(leftover, 1)) ans-=dp[sza-1][0][1];
		}
		memset(dp, 0, sizeof(dp));
		solve(dy, dd);
		leftover=extract(szb, dd);
		if (parity(leftover, 0)) ans+=dp[szb-1][0][0];
		if (parity(leftover, 1)) ans+=dp[szb-1][0][1];
		print(ans);
	}
}
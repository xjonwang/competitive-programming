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

ll inv(const ll& i, const ll& m) {
  return i <= 1 ? i : m - (ll)(m/i) * inv(m % i, m) % m;
}

void solve() {
	ll n, m, x1, y1, x2, y2; read(n, m, x1, y1, x2, y2);
	vt<vt<bool>> dr(n+1, vt<bool>(m+1, 0)), dl(n+1, vt<bool>(m+1, 0)), ur(n+1, vt<bool>(m+1, 0)), ul(n+1, vt<bool>(m+1, 0));
	string dir; read(dir);
	ll bounces=0;
	while (true) {
		if (!dir.compare("DL")) {
			if (x1+y1 == x2+y2 && x2>=x1) { print(bounces); break; }
			if (y1-1 < n-x1) {
				x1+=y1-1, y1=1;
				dir="DR";
				if (dl[x1][y1]) { print(-1); break; }
				dl[x1][y1]=1;
			} else if (y1-1 > n-x1) {
				y1-=n-x1, x1=n;
				dir="UL";
				if (dl[x1][y1]) { print(-1); break; }
				dl[x1][y1]=1;
			} else {
				y1=1, x1=n;
				dir="UR";
				if (dl[x1][y1]) { print(-1); break; }
				dl[x1][y1]=1;
			}
		} else if (!dir.compare("DR")) {
			if (x2-x1 == y2-y1 && x2>=x1) { print(bounces); break; }
			if (m-y1 < n-x1) {
				x1+=m-y1, y1=m;
				dir="DL";
				if (dr[x1][y1]) { print(-1); break; }
				dr[x1][y1]=1;
			} else if (m-y1 > n-x1) {
				y1+=n-x1, x1=n;
				dir="UR";
				if (dr[x1][y1]) { print(-1); break; }
				dr[x1][y1]=1;
			} else {
				y1=m, x1=n;
				dir="UL";
				if (dr[x1][y1]) { print(-1); break; }
				dr[x1][y1]=1;
			}
		} else if (!dir.compare("UL")) {
			if (x1-x2 == y1-y2 && x2<=x1) { print(bounces); break; }
			if (y1-1 < x1-1) {
				x1-=y1-1, y1=1;
				dir="UR";
				if (ul[x1][y1]) { print(-1); break; }
				ul[x1][y1]=1;
			} else if (y1-1 > x1-1) {
				y1-=x1-1, x1=1;
				dir="DL";
				if (ul[x1][y1]) { print(-1); break; }
				ul[x1][y1]=1;
			} else {
				y1=1, x1=1;
				dir="DR";
				if (ul[x1][y1]) { print(-1); break; }
				ul[x1][y1]=1;
			}
		} else if (!dir.compare("UR")) {
			if (x1+y1 == x2+y2 && x2<=x1) { print(bounces); break; }
			if (m-y1 < x1-1) {
				x1-=m-y1, y1=m;
				dir="UL";
				if (ur[x1][y1]) { print(-1); break; }
				ur[x1][y1]=1;
			} else if (m-y1 > x1-1) {
				y1+=x1-1, x1=1;
				dir="DR";
				if (ur[x1][y1]) { print(-1); break; }
				ur[x1][y1]=1;
			} else {
				y1=m, x1=1;
				dir="DL";
				if (ur[x1][y1]) { print(-1); break; }
				ur[x1][y1]=1;
			}
		}
		//cout << x1 << " " << y1 << " " << dir << endl;
		bounces++;
	}
}

int main() {
    ios::sync_with_stdio(0);
	cin.tie(0);
    int t; read(t);
    FOR(t) solve();
    return 0;
}
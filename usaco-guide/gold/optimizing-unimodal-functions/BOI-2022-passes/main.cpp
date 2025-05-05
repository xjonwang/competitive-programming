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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	string x; read(x);
	int n=sz(x);
	unordered_map<char, int> id;
	FOR(n) if (!id.count(x[i])) id[x[i]]=sz(id);
	int m=sz(id);
	vt<int> v(n);
	FOR(n) v[i]=id[x[i]];
	vt<vt<int>> cnt(m, vt<int>(n+1));
	FOR(m) {
		cnt[i][0]=0;
		FOR(j, n) cnt[i][j+1]=cnt[i][j]+(v[j]==i);
	}
	vt<vt<ll>> opt(m, vt<ll>(m, 0));
	vt<vt<vt<ll>>> diff(m, vt<vt<ll>>(m, vt<ll>(n+1)));
	FOR(m) {
		FOR(j, m) {
			int mul=i==j ? 1 : 2;
			diff[i][j][0]=0;
			FOR(k, n) {
				if (v[k]!=i) continue;
				opt[i][j]+=mul*min(cnt[j][k], cnt[j][n]-cnt[j][k+1]);
				diff[i][j][k+1]=mul*(max(cnt[j][k], cnt[j][n]-cnt[j][k+1])-min(cnt[j][k], cnt[j][n]-cnt[j][k+1]));
			}
			FOR(k, n) diff[i][j][k+1]+=diff[i][j][k];
		}
	}
	vt<int> smed(m);
	FOR(m) {
		auto f=[&](ll idx) {
			return cnt[i][idx+1]>=cnt[i][n]-cnt[i][idx+1];
		};
		smed[i]=FIRSTTRUE(f, 0, n-1);
	}
	vt<vt<int>> med(1<<m, vt<int>(m));
	FOR(1<<m) {
		FOR(j, m) {
			if (i&(1<<j)) continue;
			auto f=[&](ll idx) {
				int precnt=0, postcnt=0;
				precnt+=cnt[j][idx+1];
				postcnt+=cnt[j][n]-cnt[j][idx+1];
				FOR(k, m) {
					if (i&(1<<k)) {
						precnt+=2*cnt[k][idx+1];
						postcnt+=2*(cnt[k][n]-cnt[k][idx+1]);
					}
				}
				return precnt>=postcnt;
			};
			med[i][j]=FIRSTTRUE(f, 0, n-1);
		}
	}
	vt<ll> dp(1<<m, 1e18); dp[0]=0;
	FOR(i, 1, 1<<m) {
		FOR(j, m) {
			if (i&(1<<j)) {
				ll cost=dp[i^(1<<j)];
				int mset=med[i^(1<<j)][j];
				FOR(k, m) {
					int mopt=smed[k];
					if (i&(1<<k)) {
						cost+=opt[j][k]+diff[j][k][max(mopt, mset)+1]-diff[j][k][min(mopt, mset)+1];
					}
				}
				umin(dp[i], cost);
			}
		}
	}
	if (dp[(1<<m)-1]%2) write(dp[(1<<m)-1]/2, '.', 5), print();
	else print(dp[(1<<m)-1]/2);
}
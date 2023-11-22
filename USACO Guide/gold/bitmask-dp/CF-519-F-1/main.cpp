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

struct cmp {
	bool operator()(const bitset<110>& a, const bitset<110>&b) const {
		FOR(i, 109, -1, -1) {
			if (a[i]^b[i]) return b[i];
		}
		return 0;
	}
};

struct cmpv {
	bool operator()(const vt<int>& a, const vt<int>& b) const {
		auto it1=a.rbegin(), it2=b.rbegin();
		while (it1!=a.rend() && it2!=b.rend()) {
			if (*it1!=*it2) return *it1<*it2;
			it1++, it2++;
		}
		return sz(a)<sz(b);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	vt<int> primes;
	vt<bool> comp(550, 0);
	FOR(i, 2, 550) {
		if (!comp[i]) primes.pb(i);
		for (int j=0; j<sz(primes) && primes[j]*i<550; j++) {
			comp[primes[j]*i]=1;
			if (i%primes[j]==0) break;
		}
	}
	int n; read(n);
	vt<int> v(n); read(v);
	vt<vt<int>> pf(n);
	map<vt<int>, int, cmpv> cnt;
	FOR(n) {
		if (v[i]==1) {
			print(1);
			return 0;
		}
		EACH(p, primes) {
			if (v[i]==1) break;
			if (v[i]%p==0) pf[i].pb(p);
			while (v[i]%p==0) v[i]/=p;
		}
		if (v[i]!=1) pf[i].pb(v[i]);
		int m=sz(pf[i]);
		FOR(j, 1, 1<<m) {
			vt<int> f;
			FOR(k, m) if (j&(1<<k)) f.pb(pf[i][k]);
			cnt[f]++;
		}
	}
	for (auto& [k, v]:cnt) {
		if (sz(k)==1) {
			v=n-v;
			continue;
		}
		int m=sz(k), s=0;
		FOR(j, 1, (1<<m)-1) {
			vt<int> f;
			FOR(i, m) if (j&(1<<i)) f.pb(k[i]);
			s+=cnt[f]*(__builtin_popcount(j)%2 ? 1 : -1);	
		}
		v=m%2 ? n-v-s : s-(n-v);
	}
	int ans=1e9;
	FOR(n) {
		int m=sz(pf[i]);
		vt<int> u;
		FOR(j, 1, 1<<m) {
			vt<int> f;
			FOR(k, m) if (j&(1<<k)) f.pb(pf[i][k]);
			if (cnt[f]) u.pb(j);
		}
		vt<int> dp(1<<m, 1e9);
		dp[0]=0;
		FOR(j, 1<<m) {
			if (dp[j]!=1e9) {
				EACH(k, u) {
					umin(dp[j|k], dp[j]+1);
				}
			}
		}
		umin(ans, dp[(1<<m)-1]+1);
	}
	print(ans==1e9 ? -1 : ans);
}
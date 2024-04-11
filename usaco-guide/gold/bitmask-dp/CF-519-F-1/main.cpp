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
	int n, a; read(n);
	vt<int> cnt(3e5+1, 0);
	vt<vt<int>> pf(3e5+1);
	vt<vt<bool>> dp(3e5+1, vt<bool>(8, 0));
	FOR(n) {
		read(a);
		if (a==1) {
			print(1);
			return 0;
		} 
		dp[a][1]=1;
		vt<int> f;
		EACH(p, primes) {
			if (a==1) break;
			if (a%p==0) f.pb(p);
			while (a%p==0) a/=p;
		}
		if (a!=1) f.pb(a);
		int m=sz(f);
		FOR(j, 1, 1<<m) {
			int idx=1;
			FOR(k, m) if (j&(1<<k)) idx*=f[k]; 
			cnt[idx]++;
		}
	}
	FOR(i, 2, 3e5+1) {
		vt<int> f;
		a=i;
		EACH(p, primes) {
			if (a==1) break;
			if (a%p==0) f.pb(p);
			while (a%p==0) a/=p;
		}
		if (a!=1) f.pb(a);
		pf[i]=f;
		if (cnt[i]==0) continue;
		int m=sz(f), s=0;
		FOR(j, 1, (1<<m)-1) {
			int idx=1;
			FOR(k, m) if (j&(1<<k)) idx*=f[k]; 
			s+=cnt[idx]*(__builtin_popcount(j)%2 ? 1 : -1);
		}
		cnt[i]=sz(f)%2 ? n-cnt[i]-s : s-(n-cnt[i]);
	}
	FOR(i, 3e5, 1, -1) {
		bool c=0;
		FOR(j, 8) c=c||dp[i][j];
		if (!c) continue;
		vt<int> f=pf[i];
		int m=sz(f);
		FOR(j, 1, 1<<m) {
			int s=1;
			FOR(k, m) if (j&(1<<k)) s*=f[k];
			if (cnt[s]) {
				FOR(k, 2, 8) dp[i/s][k]=dp[i/s][k]||dp[i][k-1];	
			}
		}
	}
	FOR(i, 2, 8) {
		if (dp[1][i]) {
			print(i);
			return 0;
		}
	}
	print(-1);
}
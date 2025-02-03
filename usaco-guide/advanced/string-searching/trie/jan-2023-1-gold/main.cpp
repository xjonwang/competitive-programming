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

ll l, r;
string ans;
vt<char> v1;
vt<string> v2, c;
vt<ll> si;
vt<vt<int>> adj;

void dfs(int v, int i, ll idx) {
		if (idx>r) return;
		if (i==sz(v2[v])) {
			if (idx-si[v]>=l) c[v]=ans.substr(idx-si[v]-l, si[v]);
			return;
		}
		if (idx>r) return;
		int u=adj[v][i];
		if (u!=-1) {
			if (idx+si[u]>l) {
				if (sz(c[u])) ans+=c[u].substr(0, min((ll)sz(c[u]), r-idx+1));
				else dfs(u, 0, idx);
			}
			idx+=si[u];
		} else {
			if (idx>=l) ans+=v2[v][i]; 
			idx++;
		}
		dfs(v, i+1, idx);
	};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(l, r); --l, --r;
	int n; read(n);
	v1.resize(n+1), v2.resize(n+1), si.resize(n+1), adj.resize(n+1), c.assign(n+1, "");
	v1[0]='*', v2[0]="a", si[0]=1, adj[0].assign(1, -1);
	FOR(i, 1, n+1) {
		read(v1[i], v2[i]);
		si[i]=sz(v2[i]);
		adj[i].assign(si[i], -1);
	}
	FOR(i, n, 0, -1) {
		FOR(j, i-1, -1, -1) {
			FOR(k, sz(v2[j])) {
				if (v2[j][k]==v1[i]) {
					adj[j][k]=i;
					si[j]+=si[i]-1;
					umin(si[j], (ll)1e18);
				}
			}
			if (v1[i]==v1[j]) break;
		}
	}
	dfs(0, 0, 0);
	print(ans);
}
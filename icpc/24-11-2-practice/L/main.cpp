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

bool dfs(int a, int L, vt<vt<int>>& g, vt<int>& btoa, vt<int>& A, vt<int>& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vt<vt<int>>& g, vt<int>& btoa) {
	int res = 0;
	vt<int> A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		FOR(a,sz(g)) if(A[a] == 0) cur.push_back(a);
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		FOR(a,sz(g))
			res += dfs(a, 0, g, btoa, A, B);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m; read(n, m);
	vt<string> v1(n-1), v2(n-1);
	FOR(n-1) read(v1[i], v2[i]);
	string ans(m, '*');
	vt<vt<bool>> anti(m, vt<bool>(26, 0));
	vt<int> gcnt(26, 0), fill(26, 1);
	vt<unordered_set<int>> gacnt(26);
	FOR(n-1) {
		vt<int> cnt(26, 0), acnt(26, 0), tcnt(26, 0);
		FOR(j, m) {
			string &s1=v1[i], &s2=v2[i];
			tcnt[s1[j]-'a']++;
			switch (s2[j]) {
				case 'B':
					anti[j][s1[j]-'a']=1;
					break;
				case 'Y':
					anti[j][s1[j]-'a']=1;
					cnt[s1[j]-'a']++;
					break;
				case 'G':
					ans[j]=s1[j];
					cnt[s1[j]-'a']++;
					gacnt[s1[j]-'a'].insert(j);
					break;
			}
		}
		FOR(j, 26) {
			umax(gcnt[j], cnt[j]);
			if (tcnt[j]>cnt[j]) fill[j]=0;
		}
	}
	vt<vt<int>> adj(m);
	vt<char> match;
	FOR(26) {
		FOR(j, gcnt[i]-sz(gacnt[i])) match.pb('a'+i);
	}
	FOR(m) {
		FOR(j, sz(match)) if (ans[i]=='*' && !anti[i][match[j]-'a']) adj[i].pb(j);
	}
	vt<int> btoa(sz(match), -1);
	hopcroftKarp(adj, btoa);
	FOR(sz(match)) if (btoa[i]!=-1) ans[btoa[i]]=match[i];
	FOR(m) {
		if (ans[i]!='*') continue;
		FOR(j, 26) {
			if (fill[j] && !anti[i][j]) {
				ans[i]='a'+j;
				break;
			}
		}
		assert(ans[i]!='*');
	}
	print(ans);
}

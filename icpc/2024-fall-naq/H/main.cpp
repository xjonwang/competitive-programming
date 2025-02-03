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

struct gene {
	char a, b;
};

int n;
vt<char> v;
vt<int> in, in2;
vt<pii> adj;
vt<vt<int>> adj2;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n);
	adj.resize(n), adj2.resize(n), v.resize(n), in.assign(n, 0), in2.assign(n, 0);
	int x, y; char z;
	FOR(n) {
		read(x, y, z);
		v[i]=z;
		--x, --y;
		adj[i]={x, y};
		if (x<0) continue;
		adj2[x].pb(i), adj2[y].pb(i);
		in[x]++, in[y]++, in2[i]+=2;
	}
	vt<gene> g(n);
	bool ansv=0;
	string ans;
	FOR(1<<n) {
		FOR(j, n) g[j]={'.', v[j]};
		queue<int> q;
		vt<int> incopy=in;
		FOR(j, n) if (incopy[j]==0) q.push(j);
		bool valid=1;
		while (sz(q)) {
			int t=q.front(); q.pop();
			if (g[t].a!='.' && g[t].b>g[t].a) valid=0;
			auto [p1, p2]=adj[t];
			if (p1<0) continue;
			if (i&(1<<t)) swap(p1, p2);
			if (v[p1]!=v[t]) {
				if (v[p1]>v[t]) valid=0;
				if (g[p1].a!='.' && g[p1].a!=v[t]) valid=0;
				g[p1].a=v[t];
			}
			if (g[t].a!='.') {
				if (v[p2]!=g[t].a) {
					if (v[p2]>g[t].a) valid=0;
					if (g[p2].a!='.' && g[p2].a!=g[t].a) valid=0;
					g[p2].a=g[t].a;
				}
			} else {
				umax(g[p2].b, g[t].b);
			}
			if (--incopy[p1]==0) q.push(p1);
			if (--incopy[p2]==0) q.push(p2);
		}
		if (valid) {
			vt<int> incopy2=in2;
			vt<char> tans(n);
			FOR(j, n) {
				if (incopy2[j]==0) {
					tans[j]=(g[j].a!='.') ? g[j].a : g[j].b;
					q.push(j);
				}
			}
			while (sz(q)) {
				int t=q.front(); q.pop();
				auto [p1, p2]=adj[t];
				EACH(c, adj2[t]) {
					if (--incopy2[c]==0) {
						q.push(c);
					}
				}
				if (p1<0) continue;
				if (i&(1<<t)) swap(p1, p2);
				tans[t]=(g[t].a=='.') ? ((v[p2]>=g[t].b) ? v[p2] : tans[p2]) : g[t].a; 
			}
			string astr;
			FOR(j, n) astr+=v[j], astr+=tans[j];	
			if (!ansv) ans=astr;
			ansv=1;
			if (astr.compare(ans)<0) ans=astr;
		}
	}
	if (ansv) {
		FOR(i, 0, 2*n, 2) print(ans.substr(i, 2));
	} else {
		print(-1);
	}
}

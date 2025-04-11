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

void solve() {
	int n; read(n);
	string a; read(a);
	vt<pair<int, bool>> tpos, ipos, lpos;
	int tcnt=0, lcnt=0, icnt=0;	
	FOR(n) {
		switch (a[i]) {
			case 'T':
				tcnt++;
				break;
			case 'L':
				lcnt++;
				break;
			case 'I':
				icnt++;
				break;
		}
	}
	FOR(n-1) {
		string t=a.substr(i, 2);
		if (t=="LI") tpos.pb({i+1, 1});
		if (t=="IL") tpos.pb({i+1, 0});
		if (t=="TI") lpos.pb({i+1, 1});
		if (t=="IT") lpos.pb({i+1, 0});
		if (t=="TL") ipos.pb({i+1, 1});
		if (t=="LT") ipos.pb({i+1, 0});
	}
	int ma=max(tcnt, max(lcnt, icnt)), d, e;
	vt<pair<int, bool>> pos, bpos;
	if (tcnt==ma) {
		d=abs(lcnt-icnt);
		e=ma-max(lcnt, icnt);
		if (lcnt>=icnt) pos=ipos, bpos=lpos;
		else pos=lpos, bpos=ipos;
	} else if (lcnt==ma) {
		d=abs(tcnt-icnt);
		e=ma-max(tcnt, icnt);
		if (tcnt>=icnt) pos=ipos, bpos=tpos;
		else pos=tpos, bpos=ipos;
	} else {
		d=abs(tcnt-lcnt);
		e=ma-max(tcnt, lcnt);
		if (tcnt>=lcnt) pos=lpos, bpos=tpos;
		else pos=tpos, bpos=lpos;
	}
	reverse(all(pos));
	reverse(all(bpos));
	if (d==0 && e==0) {
		print(0);
	} else if (d==0 && (sz(pos) || sz(bpos))) {
		print(2*e);
		if (sz(pos)) {
			auto [p, b]=pos[0];
			if (b) FOR(2*e) print(pos[0]+i); 
		}
		else if (sz(bpos)) FOR(2*e) print(bpos[0]+i);
	} else if (sz(pos) && (3*n-3*ma)/3+sz(pos)>=d) {
		print(3*ma-n+max(d-sz(pos), 0)*3);
		FOR(2*e+2*max(d-sz(pos), 0)+(d>0)) print(pos[0]+i);
		FOR(2*(d-sz(pos))) print(pos[0]);
		FOR(i, 1, min(d, sz(pos))) print(pos[i]); 	
	} else {
		print(-1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; read(t);
	FOR(t) solve();
}

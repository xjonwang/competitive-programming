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

vt<int> attack, defense, ciel;
int n, m;

bool canWin() {
	int l=0, r=0, c=m-1;
	if (m<n) return false;
	while (l<sz(attack) && r<sz(defense)) {
		if (attack[l]>defense[r]) {
			while (c>=0 && ciel[c]<=attack[l]) c--;
			if (c<0) return false;
			l++, c--;
		} else {
			while (c>=0 && ciel[c]<=defense[r]) c--;
			if (c<0) return false;
			r++, c--;
		}
	}	
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n, m);
	ciel.resize(m);
	string s; int x;
	FOR(n) {
		read(s, x);
		if (s[0]=='A') attack.pb(x);
		else defense.pb(x);
	}
	read(ciel);
	sort(all(attack)), sort(all(defense)), sort(all(ciel), greater<int>());
	if (canWin()) {
		int a=0, d=0, c=m-1, ans1=0, ans2=0;
		while (a<sz(attack) && a<sz(ciel)) {
			if (ciel[a]>=attack[a]) ans1+=ciel[a]-attack[a++];
			else break;
		}
		vt<int> leftovers;
		while (d<sz(defense)) {
			while (c>=sz(attack) && ciel[c]<=defense[d]) leftovers.pb(ciel[c--]);
			d++, c--;
		}
		FOR(i, c, -1, -1) ans2+=ciel[i];
		EACH(l, leftovers) ans2+=l;
		EACH(a, attack) ans2-=a;
		print(max(ans1, ans2));
	} else {
		int a=0, ans=0;
		while (a<sz(attack) && a<sz(ciel)) {
			if (ciel[a]>=attack[a]) ans+=ciel[a]-attack[a++];
			else {
				print(ans);
				return 0;
			}
		}
		print(ans);
	}
}

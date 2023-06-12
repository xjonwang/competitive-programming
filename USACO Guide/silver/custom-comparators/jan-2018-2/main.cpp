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

struct Milk {
	ll amt, price, index;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	ifstream cin("rental.in");
	ofstream cout("rental.out");
	int n, m, r; cin >> n >> m >> r;
	vt<ll> milk(n), rents(r);
	vt<Milk> purchases(m);
	FOR(n) cin >> milk[i];
	FOR(m) cin >> purchases[i].amt >> purchases[i].price;
	FOR(r) cin >> rents[i];
	sort(milk.begin(), milk.end(), [] (const ll& a, const ll& b) { return a > b; });
	sort(purchases.begin(), purchases.end(), [] (const Milk& a, const Milk& b) { return a.price > b.price; });
	sort(rents.begin(), rents.end());
	vt<ll> indices; indices.pb(0);
	ll cowSum = 0, milkSum = 0;
	EACH(cow, milk) indices.pb(cowSum + cow), cowSum += cow;
	EACH(purchase, purchases) indices.pb(milkSum + purchase.amt), purchase.index = milkSum, milkSum += purchase.amt;
	sort(indices.begin(), indices.end());
	indices.erase(unique(indices.begin(), indices.end()), indices.end());
	ll s = sz(indices);
	vt<ll> diffs(s, 0), prefix(s); prefix[0] = 0;
	EACH(purchase, purchases) {
		diffs[lower_bound(indices.begin(), indices.end(), purchase.index) - indices.begin()] += purchase.price;
		diffs[lower_bound(indices.begin(), indices.end(), purchase.index + purchase.amt) - indices.begin()] -= purchase.price;
	}
	ll add = 0;
	FOR(i, 1, s) {
		add += diffs[i-1];
		prefix[i] = prefix[i-1] + add * (indices[i] - indices[i-1]);
	}
	ll milkIncome = prefix[lower_bound(indices.begin(), indices.end(), cowSum) - indices.begin()], rentIncome = 0;
	while (milk.size() && rents.size()) {
		ll temp = prefix[lower_bound(indices.begin(), indices.end(), cowSum - milk.back()) - indices.begin()];
		if (rents.back() > milkIncome - temp) {
			cowSum -= milk.back(); milk.pop_back();
			milkIncome = temp;
			rentIncome += rents.back(); rents.pop_back();
		} else {
			break;
		}
	}
	cout << milkIncome + rentIncome << endl;
}
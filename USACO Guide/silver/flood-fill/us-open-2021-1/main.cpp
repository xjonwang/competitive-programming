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

struct Tile {
	int x, row, col;
};

ll n, ri, ci;
vt<vt<Tile>> grid;
vt<vt<vt<bool>>> vis;
unordered_set<ll> ans;
vt<ll> b(9, 0);
vt<int> dr={1, -1, 0, 0}, dc={0, 0, 1, -1};

bool checkMoo(vt<ll>& b) {
	vt<vt<int>> color(3, vt<int>(3));
	FOR(3) FOR(j, 3) color[i][j]=b[3*i+j];
	FOR(3) {
		if ((color[i][0]==1 && color[i][1]==2 && color[i][2]==2)
			|| (color[i][0]==2 && color[i][1]==2 && color[i][2]==1)
			|| (color[0][i]==1 && color[1][i]==2 && color[2][i]==2)
			|| (color[0][i]==2 && color[1][i]==2 && color[2][i]==1)) return true;
	}
	if ((color[0][0]==2 && color[1][1]==2 && color[2][2]==1)
		|| (color[0][0]==1 && color[1][1]==2 && color[2][2]==2)
		|| (color[2][0]==2 && color[1][1]==2 && color[0][2]==1)
		|| (color[2][0]==1 && color[1][1]==2 && color[0][2]==2)) return true;
	return false;
}

void flood(ll r, ll c) {
	ll s=0, e=1;
	FOR(9) s+=b[i]*e, e*=3;
	if (r<0 || r>=n || c<0 || c>=n || vis[r][c][s]) return;
	vis[r][c][s]=1;
	if (checkMoo(b)) {
		ans.insert(s);
		return;
	}
	ll p=-1, pidx=-1;
	if (grid[r][c].x) {
		if (grid[r][c].x<0) return;
		else if (!b[grid[r][c].row*3 + grid[r][c].col]) {
			ll idx=grid[r][c].row*3 + grid[r][c].col;
			p=b[idx], pidx=idx;
			b[idx]=grid[r][c].x;
		}
	}
	FOR(4) flood(r+dr[i], c+dc[i]);
	if (p>=0) b[pidx]=p;
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n);
	grid.resize(n, vt<Tile>(n)), vis.resize(n, vt<vt<bool>>(n, vt<bool>(19683, 0)));
	char c1, c2, c3;
	FOR(n) {
		FOR(j, n) {
			read(c1, c2, c3);
			if (c1=='#') grid[i][j]={-1, 0, 0};
			else if (c1=='.') grid[i][j]={0, 0, 0};
			else if (c1=='B') ri=i, ci=j;
			else {
				if (c1=='M') grid[i][j]={1, c2-'1', c3-'1'};
				if (c1=='O') grid[i][j]={2, c2-'1', c3-'1'};
			}
		}
	}
	flood(ri, ci);
	print(sz(ans));
}
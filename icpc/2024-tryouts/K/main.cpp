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

unordered_map<char, int> cmap={{'N', 0}, {'E', 1}, {'S', 2}, {'W', 3}};
int dr[4]={1, 0, -1, 0}, dc[4]={0, 1, 0, -1};

bool walls[4][50][50];
int dist[50][50][50][50][4][4], bumps[50][50][50][50][4][4];

struct node {
	int r1, c1, r2, c2, v, d;
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, e, t, c, r; read(m, n, e); --e;
	char x1, x2;
	int sc1, sr1, d1, sc2, sr2, d2; read(sc1, sr1, x1, sc2, sr2, x2);
	--sc1, --sr1, --sc2, --sr2;
	d1=cmap[x1], d2=cmap[x2];
	read(t);
	FOR(t) {
		read(c, r); --c, --r;
		walls[0][r][c]=1;
		walls[2][r+1][c]=1;	
	}
	read(t);
	FOR(t) {
		read(c, r); --c, --r;
		walls[1][r][c]=1;
		walls[3][r][c+1]=1;
	}
	FOR(n) walls[3][i][0]=1, walls[1][i][m-1]=1;
	FOR(m) walls[2][0][i]=1, walls[0][n-1][i]=1;
	walls[2][0][e]=0;
	deque<node> q;
	dist[sr1][sc1][sr2][sc2][3][0]=1; q.push_front({sr1, sc1, sr2, sc2, 3, 0});
	while (sz(q)) {
		auto [pr1, pc1, pr2, pc2, pv, pd]=q.front(); q.pop_front();
		FOR(4) if (dist[pr1][pc1][pr2][pc2][pv][i]==0 || (dist[pr1][pc1][pr2][pc2][pv][i]==dist[pr1][pc1][pr2][pc2][pv][pd] && bumps[pr1][pc1][pr2][pc2][pv][i]>bumps[pr1][pc1][pr2][pc2][pv][pd])) dist[pr1][pc1][pr2][pc2][pv][i]=dist[pr1][pc1][pr2][pc2][pv][pd], bumps[pr1][pc1][pr2][pc2][pv][i]=bumps[pr1][pc1][pr2][pc2][pv][pd], q.push_front({pr1, pc1, pr2, pc2, pv, i});
		int r1=pr1, c1=pc1, r2=pr2, c2=pc2, v=pv, bcnt=0;
		if (pv&1) {
			if (!walls[(d1+pd)%4][pr1][pc1]) r1=pr1+dr[(d1+pd)%4], c1=pc1+dc[(d1+pd)%4];
			else bcnt++;
		}
		if (pv&2) {
			if (!walls[(d2+pd)%4][pr2][pc2]) r2=pr2+dr[(d2+pd)%4], c2=pc2+dc[(d2+pd)%4];
			else bcnt++;
		}
		if (r1==r2 && c1==c2 && (r1!=-1 || c1!=e)) continue;
		if (r1==-1 && c1==e) v&=~1, r1=0;
		if (r2==-1 && c2==e) v&=~2, r2=0;
		if (dist[r1][c1][r2][c2][v][pd]==0 || (dist[r1][c1][r2][c2][v][pd]==dist[pr1][pc1][pr2][pc2][pv][pd]+1 && bumps[r1][c1][r2][c2][v][pd]>bumps[pr1][pc1][pr2][pc2][pv][pd]+bcnt)) dist[r1][c1][r2][c2][v][pd]=dist[pr1][pc1][pr2][pc2][pv][pd]+1, bumps[r1][c1][r2][c2][v][pd]=bumps[pr1][pc1][pr2][pc2][pv][pd]+bcnt, q.push_back({v&1 ? r1 : -1, c1, v&2 ? r2 : -1, c2, v, pd});
	}
	int a1=INT_MAX, a2=INT_MAX;
	FOR(4) umin(a1, dist[0][e][0][e][0][i]), umin(a2, bumps[0][e][0][e][0][i]);
	print(a1-1, a2);
}
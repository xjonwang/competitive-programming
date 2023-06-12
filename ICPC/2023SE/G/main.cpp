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

ll n; // number of nodes
vector<vector<ll>> adj; // adjacency list of graph

vt<ll> dists;
vt<pair<ll, ll>> points;
vt<vt<pair<ll, ll>>> distAdj;
vector<bool> visited;
unordered_set<int> vis;
vector<ll> tin, low;
ll timer;
bool valid;

bool checkBridge(int v, int to) {
	if (v!=0 && to!=0) return false;
	if ((v!=0 && adj[v].size() > 1) || (to!=0 && adj[to].size() > 1)) return false;
	return true;
}

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                if (!checkBridge(v, to)) valid = 0;
			}
        }
    }
}

void findBridgesValid() {
    timer = 0;
	valid = 1;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

void dfs2(ll v) {
	if (vis.count(v)) return;
	vis.insert(v);
	for (ll u : adj[v]) {
		dfs2(u);
	}
}

bool isConnected() {
	vis.clear();
	dfs2(0);
	return (vis.size() == n);
}

ld binarySearch() {
	ll l=0, r=dists.size()-1;
	while (r>l) {
		int mid = (l+r)/2;
		FOR(n) {
			adj[i].clear();
			int index = upper_bound(distAdj[i].begin(),
									distAdj[i].end(),
									make_pair(dists[mid], n+1),
									[](const pair<ll, ll>& a, const pair<ll, ll>& b) { return (a.first != b.first) ? (a.first < b.first) : (a.second < b.second); }) 
						- distAdj[i].begin();
			FOR(j, index) adj[i].push_back(distAdj[i][j].second);
		}
		if (!isConnected()) {
			l=mid+1;
		} else {
			findBridgesValid();
			if (valid) r=mid;
			else l=mid+1;
		}
	}
	return sqrt((ld) dists[l]);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(15);
	/*
	n=5;
	adj.resize(5);
	adj[0]={1, 2, 3};
	adj[1]={0, 2, 3};
	adj[2]={0, 1, 3};
	adj[3]={0, 1, 2};
	adj[4]={};
	cout << !isConnected();
	findBridgesValid();
	cout << valid;
	vt<pair<ll, ll>> test{ {1, 1}, {1, 2}, {1, 3}, {2, 0} };
	cout << upper_bound(test.begin(),
						test.end(),
						make_pair(1, 2),
						[](const pair<ll, ll>& a, const pair<ll, ll>& b) { return (a.first != b.first) ? (a.first < b.first) : (a.second < b.second); }) - test.begin();
	*/
	read(n); ++n;
	points.resize(n);
	distAdj.resize(n);
	adj.resize(n);
	points[0]=make_pair(0, 0);
	FOR(n-1) {
		cin >> points[i+1].first >> points[i+1].second;
	}
	FOR(n) {
		FOR(j, n) {
			if (i==j) continue;
			distAdj[i].push_back({(points[i].first-points[j].first)*(points[i].first-points[j].first) + (points[i].second-points[j].second)*(points[i].second-points[j].second), j});
			if (i<j) dists.push_back((points[i].first-points[j].first)*(points[i].first-points[j].first) + (points[i].second-points[j].second)*(points[i].second-points[j].second));
		}
	}
	FOR(n) sort(distAdj[i].begin(), distAdj[i].end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) { return (a.first != b.first) ? (a.first < b.first) : (a.second < b.second); });
	sort(dists.begin(), dists.end());
	auto it = unique(dists.begin(), dists.end(), [](const ll& a, const ll& b) { return a-b==0; });
	dists.resize(distance(dists.begin(), it));	
	cout << binarySearch();
}

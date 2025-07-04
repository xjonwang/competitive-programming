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
#define eb emplace_back
#define pb push_back
#define rsz resize
#define asn assign
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

struct ST {
	int n, h;
	vt<int> sum, pre, delta, len;
	ST(int a_n, const vt<int>& a_len) : n(1) {
		while (n<a_n) n<<=1;
		h=32-__builtin_clz(n);
		sum.asn(2*n, 0), pre.asn(2*n, 0), delta.asn(2*n, INT_MAX), len.asn(2*n, 0);
		FOR(a_n) len[n+i]=a_len[i];
		FOR(i, n-1, 0, -1) len[i]=len[i<<1]+len[i<<1|1];
	}
	void apply(int i, int x) {
		sum[i]=len[i]*x;
		pre[i]=max(0, sum[i]);
		if (i<n) delta[i]=x;
	}
	void build(int i) {
		for (; i>>=1;) {
			if (delta[i]!=INT_MAX) sum[i]=len[i]*delta[i], pre[i]=max(0, sum[i]);
			else sum[i]=sum[i<<1]+sum[i<<1|1], pre[i]=max(pre[i<<1], sum[i<<1]+pre[i<<1|1]);
		}
	}
	void push(int i) {
		if (delta[i]!=INT_MAX) {
			apply(i<<1, delta[i]);
			apply(i<<1|1, delta[i]);
			delta[i]=INT_MAX;
		}
	}
	void propagate(int i) {
		FOR(j, h-1, 0, -1) {
			push(i>>j);
		}
	}
	void set(int l, int r, int x) {
		l+=n, r+=n;
		int l0=l, r0=r-1;
		propagate(l0), propagate(r0);
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) apply(l++, x);
			if (r&1) apply(--r, x);
		}
		build(l0), build(r0);
	}
	int query_pre(int x) {
		if (pre[1]<=x) return n;
		int idx=1;
		while (idx<n) {
			push(idx);
			if (pre[idx<<1]>x) idx=idx<<1;
			else x-=sum[idx<<1], idx=idx<<1|1;
		}
		return idx-n;
	}
	int query_sum(int l, int r) {
		l+=n, r+=n;
		propagate(l), propagate(r-1);
		int ret=0;
		for (; l<r; l>>=1, r>>=1) {
			if (l&1) ret+=sum[l++];
			if (r&1) ret+=sum[--r];
		}
		return ret;
	}
	int query_slope(int i) {
		i+=n;
		propagate(i);
		return sum[i]/len[i];
	}
};

int n, m;

class IQuery {
public:
	virtual void process(ST& st, map<int, int>& idx, const vt<int>& ridx) = 0;
};

class Reconfig : public IQuery {
private:
	int l, r, d;
public:
	Reconfig(int l, int r, int d) : l(l), r(r), d(d) {}
	void process(ST& st, map<int, int>& idx, const vt<int>& ridx) override {
		st.set(idx[l], idx[r], d);
	}
};

class Ride : public IQuery {
private:
	int h;
public:
	Ride(int h) : h(h) {}
	void process(ST& st, map<int, int>& idx, const vt<int>& ridx) override {
		int ub=st.query_pre(h);
		if (ub>=m) {
			print(n);
			return;
		}
		int slope=st.query_slope(ub);
		int sum=st.query_sum(0, ub);
		print(ridx[ub]+(h-sum)/slope);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	read(n);
	char c; int x, y, z;
	vt<unique_ptr<IQuery>> q;
	vt<int> ridx={0, n};
	while (true) {
		read(c);
		if (c=='E') break;
		switch (c) {
			case 'I':
				read(x, y, z); --x;
				q.eb(new Reconfig(x, y, z));
				ridx.pb(x), ridx.pb(y);
				break;
			case 'Q':
				read(x);
				q.eb(new Ride(x));
				break;
		}
	}
	sort(all(ridx));
	ridx.erase(unique(all(ridx)), ridx.end());
	m=sz(ridx);
	map<int, int> idx;
	FOR(sz(ridx)) idx[ridx[i]]=i;
	vt<int> len(m-1);
	FOR(m-1) len[i]=ridx[i+1]-ridx[i];
	ST st(m-1, len);
	EACH(x, q) x->process(st, idx, ridx);
}
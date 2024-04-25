#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define f first
#define s second

#define vt vector
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, k; cin>>n>>m>>k;
	vt<pii> v(n);
	for (int i=0; i<n; i++) cin>>v[i].f>>v[i].s;
	sort(all(v), greater<pii>());
	deque<pii> q; q.pb({INT_MAX, m});
	ll ans=0;
	for (int i=0; i<n; i++) {
		int cnt=0;
		while (sz(q) && cnt<v[i].s) {
			pii& t=q.front();
			if (t.f-k<v[i].f) break;
			if (v[i].s-cnt>=t.s) {
				cnt+=t.s;
				q.pop_front();
			} else {
				t.s-=v[i].s-cnt;
				cnt=v[i].s;
			}
		}
		q.push_back({v[i].f, cnt});
		ans+=cnt;
	}
	cout << ans << endl;
}

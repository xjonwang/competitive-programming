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
	int n; cin>>n;
	vt<string> v(n-1);
	for (int i=0; i<n-1; i++) cin>>v[i];
	vt<vt<int>> parity(n, vt<int>(n, 0));
	int ans=0;
	for (int i=n-2; i>=0; i--) {
		for (int j=0; j<n-i-1; j++) {
			if (v[i][j]-'0'!=parity[i][i+j+1]) {
				ans++;
				parity[i][i+j+1]+=1;
				parity[i][i+j+1]%=2;
				for (int k=j+1; k<n-i-1; k++) {
					parity[i][i+k+1]+=parity[i+j+1][i+k+1];
					parity[i][i+k+1]%=2;
				}
			}
		}
	}
	cout << ans << endl;
}

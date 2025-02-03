#include <bits/stdc++.h>
using namespace std;

#define REP2(i, n) for (int i = 0; i < (n); i++)
#define REP3(i, a, b) for (int i = (a); i <= (b); i++)
#define PER2(i, n) for (int i = (n) - 1; i >= 0; i--)
#define PER3(i, a, b) for (int i = (a); i >= (b); i--)
#define GET_MACRO(a, b, c, d, ...) d
#define rep(...) GET_MACRO(__VA_ARGS__, REP3, REP2)(__VA_ARGS__)
#define per(...) GET_MACRO(__VA_ARGS__, PER3, PER2)(__VA_ARGS__)
#define each(i, a) for (auto &i : (a))

template <typename T> vector<T> ndvec(size_t size, T initial_value) {
    return vector<T>(size, initial_value);
}
template <typename T, typename... U> auto ndvec(size_t head, U &&...u) {
    auto inner = ndvec<T>(u...);
    return vector<decltype(inner)>(head, inner);
}

constexpr long long c_div(long long a, long long b) { return a / b + ((a ^ b) > 0 && a % b); }
constexpr long long f_div(long long a, long long b) { return a / b - ((a ^ b) < 0 && a % b); }

#ifdef LOCAL
#include "/home/rayb/comp-programming/debug/debug.hpp"
#define dbg(...) Debug(#__VA_ARGS__, __LINE__, __FUNCTION__, __VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define int long long

// insert snippets below:
template <typename T, typename U> T last_true(T l, T r, U f) {
    l--;
    assert(l <= r);
    while (l < r) {
        T mid = l + (r - l + 1) / 2;
        f(mid) ? l = mid : r = mid - 1;
    }
    return l;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<tuple<int, int, int>> events;
    set<int> uni;
    rep(i, m) {
        int t, x, y;
        cin >> t >> x >> y;
        x--;
        events.emplace_back(t, x, y);
        uni.insert(x);
    }
    sort(events.begin(), events.end(), greater<decltype(events[0])>());

    if (n == 1 || uni.size() == 1) {
        cout << "-1\n";
        return;
    }

    auto ok = [&](int time) -> bool {
        int remaining = time;
        vector<int> looked(n + 1, 0);
        each(i, events) {
            const auto &[t, x, y] = i;
            if (t > time)
                continue;
            int look = time + 2 - t - (y + k - 1) / k;
            if (look > 0) {
                look -= looked[x];
                if (look > 0) {
                    remaining -= look;
                    if (remaining + 1 < t) return false;
                    looked[x] += look;
                }
            }
            
        }
        return true;
    };

    int time = last_true(0LL, (long long)3e18 + 5, ok);
    dbg(time);
    cout << time << '\n';
}

signed main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    // int t;
    // cin >> t;
    // while (t--)
    solve();
}


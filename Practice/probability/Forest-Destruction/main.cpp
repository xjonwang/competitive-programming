#include <bits/stdc++.h>
using namespace std;

#define vt vector
#define ll long long
#define ld long 
#define pii pair<int, int>

struct pt {
    double x, y;
};

int orientation(pt a, pt b, pt c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v<0) return -1;
    if (v>0) return +1;
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}

bool collinear(pt a, pt b, pt c) {return orientation(a, b, c) == 0;}

void convex_hull(vector<pt>& a, bool include_collinear=false) {
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if (o == 0) {
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        }
        return o<0;
    });
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i>=0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }

    vector<pt> st;
    for (int i=0; i<(int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }
    a=st;
}

double dot(pt a, pt b) {
    return a.x * b.x + a.y * b.y;
}

double angle(pt a, pt b, pt c) {
    pt ab = {b.x - a.x, b.y - a.y};
    pt ac = {c.x - a.x, c.y - a.y};
    return acos(dot(ab, ac) / (sqrt(dot(ab, ab)) * sqrt(dot(ac, ac))));
}

int main() {
    int n; cin >> n;
    double PI = 4 * atan(1);
    vt<pt> points;
    for (int i=0; i<n; i++) {
        pt temp;
        cin >> temp.x >> temp.y;
        points.push_back(temp);
    }
    convex_hull(points, true);
    int sz = points.size();
    for (int i = 0; i < sz; i++) points.push_back(points[i]);
    pt prev = points[points.size() - 1];
    int l = 0;
    int r = 1;
    int answer = sz;
    while (l < sz && r < 2 * sz - 1) {
        if (l + sz - 1 <= r) {
            prev = points[l];
            l++;
            continue;
        }
        if (collinear(points[l], points[r], prev) || collinear(points[l], points[r], points[r + 1])) {
            r++;
            continue;
        }
        double a = angle(points[l], prev, points[r]);
        double b = angle(points[r], points[r+1], points[l]);
        if (a + b + 0.000000000001 < PI) {
            answer = min(answer, r - l + 1);
            prev = points[l];
            l++;
        }
        else {
            r++;
        }
        if (l == r) r++;
    }
    cout << answer << "\n";
    return 0;
}
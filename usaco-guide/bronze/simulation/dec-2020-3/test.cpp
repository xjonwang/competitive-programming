#include <bits/stdc++.h>
using namespace std;

struct Cow {
	int x, y;
	int ind;
};

int main() {
	int n;
	cin >> n;
	vector<Cow> n_cows;
	vector<Cow> e_cows;

	for (int i = 0; i < n; i++) {
		char dir;
		int x, y;
		cin >> dir >> x >> y;
		if (dir == 'N') {
			n_cows.push_back({x, y, i});
		} else if (dir == 'E') {
			e_cows.push_back({x, y, i});
		}
	}

	sort(
		n_cows.begin(), n_cows.end(),
		[&] (const Cow& c1, const Cow& c2) { return c1.x < c2.x; }
	);
	sort(
		e_cows.begin(), e_cows.end(),
		[&] (const Cow& c1, const Cow& c2) { return c1.y < c2.y; }
	);

	vector<int> stop_pos(n, -1);
	for (const Cow& ncow : n_cows) {
		for (const Cow& ecow : e_cows) {
			// Check that the two cows will intersect.
			if (ncow.x > ecow.x && ncow.y < ecow.y) {
				// Distance they travel before reaching the other cow's line.
				int n_trav = ecow.y - ncow.y;
				int e_trav = ncow.x - ecow.x;

				// Check if the north cow blocks the east cow.
				if (n_trav < e_trav && stop_pos[ecow.ind] == -1) {
					// # Save the x-coordinate at which the east cow stops
					stop_pos[ecow.ind] = ncow.x;
				}

				// Check if the east cow blocks the north cow.
				if (n_trav > e_trav && stop_pos[ecow.ind] == -1) {
					// Save the y-coordinate at which the north cow stops
					stop_pos[ncow.ind] = ecow.y;
					// At this point we can move on- this cow won't move anymore.
					break;
				}
			}
		}
	}

	vector<int> dist(n, -1);
	for (const Cow& nc : n_cows) {
		// A cow eats a finite amount of grass if & only if this value isn't -1.
		if (stop_pos[nc.ind] != -1) {
			// Eaten is (stopped position - original position)
			dist[nc.ind] = stop_pos[nc.ind] - nc.y;
		}
	}

	for (const Cow& ec : e_cows) {
		if (stop_pos[ec.ind] != -1) {
			dist[ec.ind] = stop_pos[ec.ind] - ec.x;
		}
	}

	for (int d : dist) {
		cout << (d == -1 ? "Infinity" : to_string(d)) << '\n';
	}
}
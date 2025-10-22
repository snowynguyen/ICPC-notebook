#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// BeginCodeSnip{DSU}
class DSU {
  private:
	vector<ll> p, sz, sum;
	// stores all history info related to merges
	vector<pair<ll &, ll>> history;

  public:
	DSU(int n) : p(n), sz(n, 1), sum(n) { iota(p.begin(), p.end(), 0); }

	void init_sum(const vector<ll> a) {
		for (int i = 0; i < (int)a.size(); i++) { sum[i] = a[i]; }
	}

	int get(int x) { return (p[x] == x) ? x : get(p[x]); }

	ll get_sum(int x) { return sum[get(x)]; }

	void unite(int a, int b) {
		a = get(a);
		b = get(b);
		if (a == b) { return; }
		if (sz[a] < sz[b]) { swap(a, b); }

		// add to history
		history.push_back({p[b], p[b]});
		history.push_back({sz[a], sz[a]});
		history.push_back({sum[a], sum[a]});

		p[b] = a;
		sz[a] += sz[b];
		sum[a] += sum[b];
	}

	void add(int x, ll v) {
		x = get(x);
		history.push_back({sum[x], sum[x]});
		sum[x] += v;
	}

	int snapshot() { return history.size(); }

	void rollback(int until) {
		while (snapshot() > until) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
};
// EndCodeSnip

const int MAXN = 3e5;

DSU dsu(MAXN);

struct Query {
	int t, u, v, x;
};

vector<Query> tree[MAXN * 4];

void update(Query &q, int v, int query_l, int query_r, int tree_l, int tree_r) {
	if (query_l > tree_r || query_r < tree_l) { return; }
	if (query_l <= tree_l && query_r >= tree_r) {
		tree[v].push_back(q);
		return;
	}
	int m = (tree_l + tree_r) / 2;
	update(q, v * 2, query_l, query_r, tree_l, m);
	update(q, v * 2 + 1, query_l, query_r, m + 1, tree_r);
}

void dfs(int v, int l, int r, vector<ll> &ans) {
	int snapshot = dsu.snapshot();
	// perform all available operations upon entering
	for (Query &q : tree[v]) {
		if (q.t == 1) { dsu.unite(q.u, q.v); }
		if (q.t == 2) { dsu.add(q.v, q.x); }
	}
	if (l == r) {
		// answer type 3 query if we have one
		for (Query &q : tree[v]) {
			if (q.t == 3) { ans[l] = dsu.get_sum(q.v); }
		}
	} else {
		// go deeper into the tree
		int m = (l + r) / 2;
		dfs(2 * v, l, m, ans);
		dfs(2 * v + 1, m + 1, r, ans);
	}
	// undo operations upon exiting
	dsu.rollback(snapshot);
}

int main() {
	int n, q;
	cin >> n >> q;
	vector<ll> a(n);
	for (int i = 0; i < n; i++) { cin >> a[i]; }
	dsu.init_sum(a);

	map<pair<int, int>, int> index_added;
	for (int i = 0; i < q; i++) {
		int t;
		cin >> t;
		if (t == 0) {
			int u, v;
			cin >> u >> v;
			if (u > v) swap(u, v);
			// store index this edge is added, marks beginning of interval
			index_added[{u, v}] = i;
		} else if (t == 1) {
			int u, v;
			cin >> u >> v;
			if (u > v) swap(u, v);
			Query cur_q = {1, u, v};
			// add all edges that are deleted to interval [index added, i - 1]
			update(cur_q, 1, index_added[{u, v}], i - 1, 0, q - 1);
			index_added[{u, v}] = -1;
		} else if (t == 2) {
			int v, x;
			cin >> v >> x;
			Query cur_q = {2, -1, v, x};
			// add all sum queries to interval [i, q - 1]
			update(cur_q, 1, i, q - 1, 0, q - 1);
		} else if (t == 3) {
			int v;
			cin >> v;
			Query cur_q = {3, -1, v};
			// add all output queries to interval [i, i]
			update(cur_q, 1, i, i, 0, q - 1);
		}
	}

	// add all edges that are not deleted to interval [index added, q - 1]
	for (auto [edge, index] : index_added) {
		if (index != -1) {
			Query cur_q = {1, edge.first, edge.second};
			update(cur_q, 1, index, q - 1, 0, q - 1);
		}
	}

	vector<ll> ans(q, -1);
	dfs(1, 0, q - 1, ans);
	for (int i = 0; i < q; i++) {
		if (ans[i] != -1) { cout << ans[i] << "\n"; }
	}
}
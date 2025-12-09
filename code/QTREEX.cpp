#include <bits/stdc++.h>
using namespace std;

const int N = 10002;
const int INF = 1e9;
int LGN;

struct TEdge {
    int v, w, edgeID;
};

vector<TEdge> E;

vector<TEdge> g[N]; 
int n;

struct TSegTree {
    vector<int> f_max, f_min;
    vector<short> lazy_negate;
    TSegTree () {}

    TSegTree (int n) {
        f_max.assign(4 * n, 0);
        f_min.assign(4 * n, 0);
        lazy_negate.assign(4 * n, false);
    }  

    private:

    void negate_node(int id) {
        int temp_max = f_max[id], temp_min = f_min[id];
        f_max[id] = -temp_min;
        f_min[id] = -temp_max;
        lazy_negate[id] ^= true;
    }

    void compute_from_children(int id) {
        f_max[id] = max(f_max[id * 2], f_max[id * 2 + 1]);
        f_min[id] = min(f_min[id * 2], f_min[id * 2 + 1]);
    }

    void down(int id) {
        if (lazy_negate[id]) {
            negate_node(id*2);
            negate_node(id*2+1);
            lazy_negate[id] = false;
        }
    }

    void update(int id, int l, int r, int p, int v) {
        if (r < p || p < l) 
            return;
        if (l == r) 
            f_max[id] = f_min[id] = v;
        else {
            down(id);
            int m = (l + r) / 2;
            update(id * 2, l, m, p, v);
            update(id * 2 + 1, m + 1, r, p, v);
            compute_from_children(id);
        }
    }

    void negate(int id, int l, int r, int u, int v) {
        if (r < u || v < l)
            return;
        if (u <= l && r <= v) {
            negate_node(id);
        }
        else {
            down(id);
            int m = (l + r) / 2;
            negate(id * 2, l, m, u, v);
            negate(id * 2 + 1, m + 1, r, u, v);
            compute_from_children(id);
        }

    }

    int get(int id, int l, int r, int u, int v) {   
        if (r < u || v < l)
            return -INF; 
        if (u <= l && r <= v) 
            return f_max[id];
        down(id);
        int m = (l + r) / 2;
        return max(get(id * 2, l, m, u, v), get(id * 2 + 1, m + 1, r, u, v));
    }

    public: 
    void update(int p, int v) {
        update(1, 1, n, p, v);
    }

    int get(int u, int v) {
        return get(1, 1, n, u, v);
    }

    void negate(int u, int v) {
        negate(1, 1, n, u, v);
    }
} st;


void enter() {
    cin >> n;
    for (int i=1; i<=n; ++i) {
        g[i].resize(0);
    }
    for (int i=1, u, v, w; i<n; ++i) {
        cin >> u >> v >> w;
        g[u].push_back({v, w, i});
        g[v].push_back({u, w, i});
    }
}

vector<int> visited, parent, weight, heavy, depth, flattenedPos; 
vector<vector<int > > p;
vector<int> downNodeOfEdge;

void dfs_init(int u, int p) {
    parent[u] = p;
    weight[u] = 1;
    visited[u] = true;
    for (auto [v, w, eid] : g[u]) {
        if (v == p || visited[v]) 
            continue;
        depth[v] = depth[u] + 1;
        downNodeOfEdge[eid] = v;
        E[eid] = {v, w, eid};
        dfs_init(v, u);
        weight[u] += weight[v];
    }
    for (auto [v, w, eid] : g[u]) { 
        if (v == p) 
            continue;
        if (weight[v] > weight[heavy[u]]) 
            heavy[u] = v;
    }
}

vector<int> chainID, chainHead, chainParent, chainDepth;
vector<int> flattenedTree;
int currentChainCount = 1, currentFlattenedPos;

void dfs_hld(int u, int p) {

    chainID[u] = currentChainCount - 1;
    flattenedPos[u] = currentFlattenedPos;
    flattenedTree[currentFlattenedPos] = u;
    currentFlattenedPos += 1;
    if (chainHead.size() < currentChainCount) { 
        // chainHead wasn't assigned => u begins a chain
        chainHead.push_back(u);
        if (p > 0) { // if valid p => chain has a chain parent
            //chainParent[currentChainCount - 1] = chainID[p];
            chainParent.push_back(chainID[p]);
            chainDepth.push_back(chainDepth[chainID[p]] + 1);
        }
    }

    if (heavy[u] != 0) {
        dfs_hld(heavy[u], u);
    }

    for (auto [v, w, eid] : g[u]) {
        if (p == v)
            continue;
        if (v != heavy[u]) {
            currentChainCount += 1;
            dfs_hld(v, u);
        }
        st.update(flattenedPos[v], w);
    }
}



void init() {
    LGN = log2(n + 1) + 1;
    p.assign(LGN, vector<int> (n + 1, 0));
    E.assign(n + 1, TEdge());
    st = TSegTree(n);

    visited.assign(n + 1, false);
    parent.assign(n + 1, 0);
    weight.assign(n + 1, 0);
    heavy.assign(n + 1, 0);
    depth.assign(n + 1, 0);
    downNodeOfEdge.assign(n + 1, -1);
    dfs_init(1, 0);             

    for (int u=1; u<=n; ++u) 
        p[0][u] = parent[u];
    for (int k=1; k<LGN; ++k) 
        for (int u=1; u<=n; ++u) 
            p[k][u] = p[k-1][p[k-1][u]];

    chainID.assign(n + 1, -1);
    chainHead.assign(0, 0);
    chainParent.assign(1, -1); // first chain has no parent
    chainDepth.assign(1, 0); // first chain has depth 0
    visited.assign(n + 1, false);
    flattenedPos.assign(n + 1, 0);
    flattenedTree.assign(n + 1, 0);
    currentChainCount = 1;
    currentFlattenedPos = 1;
    dfs_hld(1, -1);
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int k=LGN-1; k>=0; --k) {
        if (depth[v] - (1 << k) >= depth[u]) 
            v = p[k][v];
    }
    if (u == v) 
        return u;  
    for (int k=LGN-1; k>=0; --k) {
        if (p[k][u] != p[k][v]) {
            u = p[k][u];
            v = p[k][v];
        }
    }
    return p[0][u];
}

void negatePath(int u, int a) {
    // from u to a, a guranteed ancestor of u
    while (chainID[u] != chainID[a]) {
        int head = chainHead[chainID[u]];
        st.negate(flattenedPos[head], flattenedPos[u]);
        u = parent[head];
    }
    if (u == a) 
        return; 
    st.negate(flattenedPos[a] + 1, flattenedPos[u]); 
}

int getPath(int u, int a) {
    // from u to a, a guranteed ancestor of u
    int res = -INF;
    while (chainID[u] != chainID[a]) {
        int head = chainHead[chainID[u]];
        int c = st.get(flattenedPos[head], flattenedPos[u]);
        u = parent[head];
        res = max(res, c);
    }
    if (u == a) 
        return res;  
    int c = st.get(flattenedPos[a] + 1, flattenedPos[u]); 
    return max(c, res);
}

void process() {
    string type;
    int x, y;
    do {
        cin >> type;
        if (type == "DONE")
            return;
        cin >> x >> y;
        if (type == "CHANGE") {
            int eid = x;
            int val = y;
            int v = E[eid].v;
            int pos = flattenedPos[v];
            st.update(pos, val);
        } else if (type == "NEGATE") {
            if (x == y) continue;
            int a = lca(x, y);
            if (x == a) {
                negatePath(y, a);
            } else if (y == a) {
                negatePath(x, a);
            } else {
                negatePath(x, a);
                negatePath(y, a);
            }
        } else if (type == "QUERY") {
            int res = -INF;
            if (x == y)
                res = 0;
            else {            
                int a = lca(x, y);
                if (x == a) {
                    res = getPath(y, a);
                } else if (y == a) {
                    res = getPath(x, a);
                } else {
                    res = max(getPath(x, a), getPath(y, a));
                }
            }
            cout << res << endl;
        }
    } while (true);

}

#define task "QTREEX"

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    if (fopen (task".INP", "r")) {
        freopen (task".INP", "r", stdin);
        freopen (task".OUT", "w", stdout);
    } 

    int tt; cin >> tt;
    for (int ti = 1; ti <= tt; ++ti) {
        enter();
        init();
        process();
        tt = tt;
    }
    return 0;
}

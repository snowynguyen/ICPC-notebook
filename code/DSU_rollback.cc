#include <bits/stdc++.h>
using namespace std;

class DSURollback {
private:
    vector<int> parent;
    vector<int> rank;
    int components;
    stack<tuple<int, int, int, int>> history;
    
public:
    DSURollback(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        components = n;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        while (x != parent[x]) {
            x = parent[x];
        }
        return x;
    }
    
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        
        if (x == y) {
            history.push({-1, -1, -1, components});
            return false;
        }
        
        if (rank[x] < rank[y]) {
            swap(x, y);
        }
        
        history.push({y, parent[y], rank[x], components});
        
        parent[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
        components--;
        
        return true;
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    
    int getComponents() {
        return components;
    }
    
    void rollback() {
        if (history.empty()) return;
        
        auto [node, old_parent, old_rank, old_components] = history.top();
        history.pop();
        
        if (node != -1) {
            parent[node] = old_parent;
            int root = find(node);
            rank[root] = old_rank;
        }
        components = old_components;
    }
    
    int checkpoint() {
        return history.size();
    }
    
    void rollbackTo(int checkpoint) {
        while ((int)history.size() > checkpoint) {
            rollback();
        }
    }
};

struct Edge {
    int u, v;
    int start_time, end_time; // edge exists in time range [start_time, end_time)
};

struct Query {
    int type; // 0 = connectivity query, 1 = component count query
    int u, v; // for connectivity query
    int time;
    int id; // original query index
};

class OfflineDynamicConnectivity {
private:
    int n; // number of nodes
    DSURollback dsu;
    vector<string> answers;
    
    // Divide and conquer on time interval [l, r)
    void divideConquer(int l, int r, vector<Edge>& edges, vector<Query>& queries) {
        // Separate queries in this time range
        vector<Query> current_queries;
        // Valid queries
        for (auto& q : queries) {
            if (q.time >= l && q.time < r) {
                current_queries.push_back(q);
            }
        }
        
        // Base case: single time point
        if (l + 1 == r) {
            for (auto& q : current_queries) {
                if (q.type == 0) {
                    // Connectivity query
                    if (dsu.connected(q.u, q.v)) {
                        answers[q.id] = "YES";
                    } else {
                        answers[q.id] = "NO";
                    }
                } else {
                    // Component count query
                    answers[q.id] = to_string(dsu.getComponents());
                }
            }
            return;
        }
        
        if (current_queries.empty()) {
            return;
        }
        
        int mid = (l + r) / 2;
        int checkpoint = dsu.checkpoint();
        
        // Find edges that span the entire interval [l, r)
        vector<Edge> left_edges, right_edges, spanning_edges;
        
        for (auto& e : edges) {
            if (e.end_time <= l || e.start_time >= r) {
                // Edge doesn't exist in [l, r)
                continue;
            }
            
            if (e.start_time <= l && e.end_time >= r) {
                // Edge spans entire [l, r)
                spanning_edges.push_back(e);
                dsu.unite(e.u, e.v);
            } else if (e.end_time <= mid) {
                // Edge only in left half
                left_edges.push_back(e);
            } else if (e.start_time >= mid) {
                // Edge only in right half
                right_edges.push_back(e);
            } else {
                // Edge spans across mid, add to both
                left_edges.push_back(e);
                right_edges.push_back(e);
            }
        }
        
        // Recurse on left half
        divideConquer(l, mid, left_edges, queries); // trong bc nay luu checkpoint lai het roi
        
        // Recurse on right half
        divideConquer(mid, r, right_edges, queries); // trong bc nay cung luu checkpoint laij het r
        
        // Rollback all changes made in this call
        dsu.rollbackTo(checkpoint);
    }
    
public:
    OfflineDynamicConnectivity(int n) : n(n), dsu(n) {}
    
    vector<string> solve(vector<Edge>& edges, vector<Query>& queries, int max_time) {
        answers.resize(queries.size());
        divideConquer(0, max_time, edges, queries);
        return answers;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    // Read edges with time ranges
    vector<Edge> edges;
    map<pair<int,int>, int> edge_start; // tracks when each edge was added
    
    int current_time = 0;
    vector<Query> queries;
    
    for (int i = 0; i < k; i++) {
        string op;
        cin >> op;
        
        if (op == "+") {
            int u, v;
            cin >> u >> v;
            u--; v--;
            if (u > v) swap(u, v);
            
            edge_start[{u, v}] = current_time;
            
        } else if (op == "-") {
            int u, v;
            cin >> u >> v;
            u--; v--;
            if (u > v) swap(u, v);
            
            if (edge_start.count({u, v})) {
                edges.push_back({u, v, edge_start[{u, v}], current_time});
                edge_start.erase({u, v});
            }
            
        } else if (op == "connected") {
            int u, v;
            cin >> u >> v;
            u--; v--;
            queries.push_back({0, u, v, current_time, (int)queries.size()});
            
        } else if (op == "?") {
            queries.push_back({1, -1, -1, current_time, (int)queries.size()});
        }
        
        current_time++;
    }
    
    // Add any remaining edges that were never removed
    for (auto& [edge_pair, start] : edge_start) {
        edges.push_back({edge_pair.first, edge_pair.second, start, current_time});
    }
    
    OfflineDynamicConnectivity solver(n);
    vector<string> answers = solver.solve(edges, queries, current_time);
    
    for (auto& ans : answers) {
        cout << ans << "\n";
    }
    
    return 0;
}
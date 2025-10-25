struct DSU{
    vector<int> r;
    int n;

    DSU (int n) : n(n) {
        r.assign(n+1, -1);
    }

    int root (int u) {
        if (r[u] < 0) return u;
        return r[u] = root(r[u]);
    }

    void mergetree (int ru, int rv) {
        ru = root(ru);
        rv = root(rv);
        if (ru == rv) return;
        if (r[ru] > r[rv]) 
            swap(ru, rv);
        r[ru] += r[rv];
        r[rv] = ru;
    }
};
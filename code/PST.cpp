/*You are given an integer sequence a0, a1, ..., aN-1. 
Process the following Q queries in order:
Query Format: li ri ki
Task: Print the (ki + 1)-th smallest value in the subarray 
        (ali, ali+1, ..., ari-1).
*/
#include<bits/stdc++.h>
using namespace std;

struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

int n;
vector<int> a;

const int tl = 0, tr = 2e5 + 1;

struct PST {
    vector<Vertex*> roots; 

    Vertex* build(int tl, int tr) {
        if (tl == tr)
            return new Vertex(0);
        int tm = (tl + tr) / 2;
        return new Vertex(build(tl, tm), build(tm+1, tr));
    }

    Vertex* update(Vertex* v, int tl, int tr, int pos) {
        if (tl == tr)
            return new Vertex(v->sum+1);
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return new Vertex(update(v->l, tl, tm, pos), v->r);
        else
            return new Vertex(v->l, update(v->r, tm+1, tr, pos));
    }

    int find_kth(Vertex* vl, Vertex *vr, int tl, int tr, int k) {
        if (tl == tr)
            return tl;
        int tm = (tl + tr) / 2;
        int left_count = vr->l->sum - vl->l->sum;
        if (left_count > k)
            return find_kth(vl->l, vr->l, tl, tm, k);
        return find_kth(vl->r, vr->r, tm+1, tr, k-left_count);
    }

    int find_kth(int l, int r, int k) {
        // l, r, k are zero indexed, [l, r)
        return find_kth(roots[l], roots[r], tl, tr, k);
    }

    PST () {
        roots.push_back(build(tl, tr));
        for (int i = 0; i < a.size(); i++) {
            roots.push_back(update(roots.back(), tl, tr, a[i]));
        }
    }

};

int main() {
    int q;
    cin >> n >> q;
    a.resize(n);
    for (int &o:a) cin >> o;
    set<int> sa(a.begin(), a.end());
    vector<int> fa(sa.begin(), sa.end());
    for (int &x:a)x=lower_bound(fa.begin(), fa.end(),x)-fa.begin();
    
    PST pst;
    for (int i=0,l,r,k; i<q; ++i) {
        cin >> l >> r >> k;
        cout << fa[pst.find_kth(l, r, k)] << "\n";
    }

    return 0;
}
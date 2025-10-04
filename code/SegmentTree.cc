// Official version
// Source: https://wiki.vnoi.info/algo/data-structures/segment-tree-basic.md

#include <bits/stdc++.h>

using namespace std;

const int inf  = 1e9 + 7;
const int maxN = 1e5 + 7;

int n, q;
int a[maxN];
long long st[4 * maxN], lazy[4 * maxN];

void build(int id, int l, int r) {
    if (l == r) {
        st[id] = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    st[id] = max(st[2 * id], st[2 * id + 1]);
}

// Cập nhật nút đang xét và đẩy giá trị lazy xuống các nút con
void fix(int id, int l, int r) {
    if (!lazy[id]) return; // nut do = 0 thi update cc gi nua
    st[id] += lazy[id];

    // Nếu id không phải là nút lá thì đẩy giá trị xuống các nút con
    if (l != r){
        lazy[2 * id] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
    }

    lazy[id] = 0; // already reset here
}

void update(int id, int l, int r, int u, int v, int val) {
	// Update the whole range [u, v]
    fix(id, l, r); // lay cai gia tri do ra, roi day xuong may thang khac
    if (l >  v || r <  u) return;
    if (l >= u && r <= v) {
        lazy[id] += val; // sudo apt update 
        fix(id, l, r); // sudo apt upgrade
        return;
    }
    int mid = l + r >> 1;
    update(2 * id, l, mid, u, v, val);
    update(2 * id + 1, mid + 1, r, u, v, val);
    st[id] = max(st[2 * id], st[2 * id + 1]);
}

long long get(int id, int l, int r, int u, int v) { // in this code, we reduce l, r such that it matches u, v
    fix(id, l, r); // luon luon fix truoc khi lay!!!
    if (l >  v || r <  u) return -inf;
    if (l >= u && r <= v) return st[id];

    int mid  = l + r >> 1;
    long long get1 = get(2 * id, l, mid, u, v);
    long long get2 = get(2 * id + 1, mid + 1, r, u, v);
    return max(get1, get2);
}
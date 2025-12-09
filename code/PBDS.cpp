// Required PBDS headers
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

template<typename Key, typename Value>
using ordered_map = tree<Key, Value, less<Key>, rb_tree_tag, 
    tree_order_statistics_node_update>;

void print(ordered_set<int> s) {
    for (int x : s)
        cout << x << " "; 
    cout << endl;
}

int main() {
    ordered_set<int> s;

    s.insert(10); s.insert(20); s.insert(30); 
    print(s);               // 10 20 30
    s.erase(20); print(s);  // 10 30
    if (s.find(20) != s.end())
        cout << "20 is found\n";
    else
        cout << "20 is not found\n";
    // 20 is not found
    
    s.insert(20); s.insert(60); s.insert(-10); // -10 10 20 30 60
    // lower_bound(x) returns iterator to the first element >= x.
    auto it = s.lower_bound(15);
    if (it != s.end())
        cout << *it << "\n";  // Output: 20
    
    // upper_bound(x) returns iterator to the first element > x.
    it = s.upper_bound(20);
    if (it != s.end())
        cout << *it << "\n";  // Output: 30

    // find_by_order(k) returns iterator to the k-th smallest ele
    cout << *s.find_by_order(-10) << endl;  // Output: 0

    // order_of_key(x) returns the number of elements strictly less than x.
    cout << s.order_of_key(25) << endl;  // Output: 3

    #define fi first 
    #define se second
    ordered_map<pair<int, int>, int> M;
    M[make_pair(4, 4)] = 3; M[make_pair(1, 4)] = 10;
    M[make_pair(4, 1)] = 120; M[make_pair(1, 1)] = 61;
    for (auto x : M) {
        cout << x.fi.fi << " " << x.fi.se << ": " << x.se << "; ";
    }
    cout << endl; 
    auto p0 = *(M.find_by_order(0)); // 1 1: 61
    cout << p0.fi.fi << " " << p0.fi.se << ": " << p0.se << endl;
    int s30 = M.order_of_key({3,0}); cout << s30 << endl; // 2
    return 0;
}
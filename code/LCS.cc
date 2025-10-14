#include<bits/stdc++.h>
using namespace std;
int main() {
    int n; cin >> n; int m; cin >> m;
    vector<int> a(n); for (int &x:a) cin >> x;
    vector<int> b(m); for (int &x:b) cin >> x;

    vector< vector< int > > f(n+1, vector<int> (m+1, 0));
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            if (a[i] == b[j]) {
                f[i+1][j+1] = f[i][j] + 1;
            } else {
                f[i+1][j+1] = max(f[i][j+1], f[i+1][j]);
            }
        }
    }

    cout << f[n][m] << endl;
    int x=n,y=m; vector<int> trace;
    while (x>0&&y>0) {
        if (a[x-1] == b[y-1]) {
            trace.push_back(a[x-1]); 
            x--;y--;
        } else if (f[x][y] == f[x-1][y]) x--;
        else y--;
    }
    for (int i=trace.size()-1; i>=0; --i) cout << trace[i] << " ";
}
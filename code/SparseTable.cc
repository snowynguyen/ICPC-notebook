// Official
// Sparse Table implementation for range minimum queries (RMQ), and range sum queries (RSQ)
// Preprocessing time: O(n log n)
// Query time: O(1)

// LG là số lớn nhất thoả 2^LG < N
// ví dụ: N = 10^5 thì LG = 16 vì 2^16 = 65536
int a[N], st[LG + 1][N];
void preprocess() {
    for (int i = 1; i <= n; ++i) st[0][i] = a[i];
    for (int j = 1; j <= LG; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            // st[j][i] -> the smallest element from i to i + 2^j. the j represents for the length
	        // ~ the smallest element from [i to 2^{j-1}] and from [i + 2^{j-1} to 2^j]
	        //                             st[j-1][i],              st[j-1][i + (1 << (j-1))]
}
int queryMin(int l, int r) {
    int k = __lg(r - l + 1); // this is the length
    return min(st[k][l], st[k][r - (1 << k) + 1]); // query from l -> k , r traces back to k such that they overlap
}

int querySum(int l, int r) {
    int len = r - l + 1;
    int sum = 0;
    // for each interval [l, r], we divide it into log_2(r - l + 1) interval whose length is 2^x
    // example: [3, 15] -> length = 13 = 1 + 4 + 8 ~ [3], [4, 7], [8, 15]
    // we can check the activated bits of length, lets call them j_1, j_2, j_3
    // obviously, the result is sum += st[j_1][l] + s[j_2][l+j_1] + s[j_3][l + j_2] (we can ensure this sequence match r)
    // from here, we can sum st[l][]
    
    for (int j = 0; (1 << j) <= len; ++j) 
        if (len >> j & 1) { // check whether j-th bit is 1 or not.
            sum = sum + st[j][l];
            l = l + (1 << j);
        }
    return sum;
}

// 2D Sparse Table

int a[M][N], st[LGM + 1][M][LGN + 1][N];
void preprocess() {
    for (int k = 0; k <= LGM; ++k) {
        for (int i = 1; i + (1 << k) - 1 <= m; ++i) {
            for (int l = 0; l <= LGN; ++l) {
                for (int j = 1; j + (1 << l) - 1 <= n; ++j) {
                    if (k == 0) {
                        if (l == 0) {
                            st[0][i][0][j] = a[i][j];
                        }
                        else {
                            st[0][i][l][j] = min(st[0][i][l - 1][j], st[0][i][l - 1][j + (1 << (l - 1))]);
                        }
                    }
                    else {
                        st[k][i][l][j] = min(st[k - 1][i][l][j], st[k - 1][i + (1 << (k - 1))][l][j]);
                    }
                }
            }
        }
    }
}

int getMin(int x, int y, int a, int b) {
    int k = __lg(a - x + 1);
    int l = __lg(b - y + 1);
    return min({ st[k][x][l][y],
                 st[k][x][l][b - (1 << l) + 1],
                 st[k][a - (1 << k) + 1][l][y],
                 st[k][a - (1 << k) + 1][l][b - (1 << l) + 1] });
}
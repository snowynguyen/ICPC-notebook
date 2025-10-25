// Max matching for unweighted bipartie graph 
// Kuhn's algorithm O(n^2)
/*
Given a **bipartite graph** $G = (X \cup Y, E)$. The vertices of $X$ are denoted $x_1, x_2, \ldots, x_m$, and the vertices of $Y$ are denoted $y_1, y_2, \ldots, y_n$.

A **matching** on $G$ is a set of edges $E' \subseteq E$ such that no two edges in $E'$ share a common vertex.

**Requirement:** Find a **maximum matching** (having the most edges) on $G$.

## Input
* **Line 1:** Contains two integers, $m$ and $n$ ($1 \le m, n \le 100$).
* **Subsequent lines:** Each line contains two positive integers, $i$ and $j$, representing an edge $(x_i, y_j) \in E$.

## Output
* **Line 1:** The number of edges in the maximum matching found ($K$).
* **$K$ subsequent lines:** Each line contains two numbers, $u$ and $v$, representing the edge $(x_u, y_v)$ chosen for the maximum matching.
*/ 
#include <bits/stdc++.h>
using namespace std;

const int N = 102;

int n, m, Assigned[N];

int Visited[N], t = 0;

vector<int> a[N];

bool visit(int u) {
    if (Visited[u] != t)
        Visited[u] = t;
    else
        return false;
    for (int i = 0; i < a[u].size(); i++) {
        int v = a[u][i];
        if (!Assigned[v] || visit(Assigned[v])) {
            Assigned[v] = u;
            return true;
        }
    }
    return false;
}

int main() {

    scanf("%d%d", &m, &n);
    int x, y;
    while (scanf("%d%d", &x, &y) > 0)
        a[x].push_back(y);
    int Count = 0;
    for (int i = 1; i <= m; i++) {
        t++;
        Count += visit(i);
    }

    printf("%d\n", Count);
    for (int i = 1; i <= n; i++)
        if (int j = Assigned[i])
            printf("%d %d\n", j, i);
}
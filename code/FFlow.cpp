#include <bits/stdc++.h> 
using namespace std;
const int N = 5001;
#define fi first
#define se second
struct TEdge
{
    int v,rit; //rit: reverse edge 
    long long cap,flow;
};
 
map<pair<int, int> , long long>  ww;
int n,m;
void enter()
{
    cin >> n >> m;
    for (int i=0,a,b,c; i<m; i++)
    {
        cin >> a >> b >> c;
        ww[{a,b}] += c;
        ww[{b,a}] += c;
    }
}

vector< TEdge> g[N];
void init()
{
    int ru, rv;
    for (pair<pair<int, int>, int> p: ww)
    {
        if (p.fi.fi < p.fi.se)
        {
            ru = g[p.fi.fi].size();
            rv = g[p.fi.se].size();
            g[p.fi.fi].push_back({p.fi.se, rv, p.se, 0});
            g[p.fi.se].push_back({p.fi.fi, ru, p.se, 0});
        }
    }
}
 
int MF = 1;
int tt;
int d[N], ni[N];
 
bool bfs()
{
    for (int i=1; i<=n; i++)
        d[i] = 0;
    d[1] = 1;
    queue<int> qu;
    int u;
    qu.push(1);
    while (!qu.empty())
    {
        u = qu.front();
        qu.pop();
        for (auto v : g[u])
        {
            if (!d[v.v])
            {
                if (v.flow + MF <= v.cap)
                {
                    d[v.v] = d[u] + 1;
                    qu.push(v.v);
                }
            }
        }
    }
    return d[n];
}
 
 
long long dfs (int u, long long ff)
{
    if (u ==n)
        return ff;
    for (;ni[u] < g[u].size(); ++ni[u])
    {
        if (d[g[u][ni[u]].v] == d[u] + 1)
        {
            int fff = dfs(g[u][ni[u]].v, min(g[u][ni[u]].cap - g[u][ni[u]].flow, ff));
            if (fff >= MF)
            {
                g[u][ni[u]].flow += fff;
                g[g[u][ni[u]].v][g[u][ni[u]].rit].flow -= fff;
                return fff;
            }
        }
    }
    return 0;
}
 
long long max_flow()
{
    long long res = 0,d;
    MF = 1 << 30;
    while (MF)
    {
        while (bfs())
        {
            for (int i=1; i<=n; i++)
                ni[i] = 0;
            do
            {
                d = dfs(1, 1<<30);
                res += d;
            } while (d);
        }
        MF >>= 1;
    }
    return res;
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    enter();
    init();
    cout << max_flow();
    return 0;
}

/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: LCA via binary lifting.  
 * Time: $O(N \log N)$ time to build, $O(\log N)$ per query.
 */
int n;
vi G[N];
int parent[LOGN][N];
int depth[N];

void dfs(int v, int p, int d){
    parent[0][v] = p;
    depth[v] = d;
    for(int nxt : G[v]){
        if(nxt != p) dfs(nxt, v, d+1);
    }
}

void init() {
    dfs(0, -1, 0); // rooted at 0
    rep(k, 0, LOGN - 1) {
        rep(v, 0, n) parent[k + 1][v] = parent[k][v] < 0 ? -1 : parent[k][parent[k][v]];
    }
}
int lca(int u, int v){
    if(depth[u] > depth[v]) swap(u, v);
    rep(k, 0, LOGN) {
        if ((depth[v] - depth[u]) >> k & 1) v = parent[k][v];
    }
    if(u == v) return u;
    for (int k = LOGN - 1; k >= 0; k--) {
        if(parent[k][u] != parent[k][v]) {
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

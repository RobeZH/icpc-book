/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: LCA via binary lifting.  
 * Time: $O(N \log N)$ time to build, $O(\log N)$ per query.
 */
typedef vector<pii> vpi;
typedef vector<vpi> graph;

struct LCA {
    vector<vi> parent;
    graph g;
    vi dep;
    vector<ll> dis;
    int lg, n;

    LCA(graph& g): n(sz(g)), dep(sz(g)), dis(sz(g)), g(g) {
        int on = 1;
        lg = 1;
        while (on < n) on *= 2, lg++;
        parent.assign(lg, dep);
        dfs(0, -1, 0, 0); // rooted at 0
        rep(k, 0, lg - 1) {
            rep(v, 0, n) {
                parent[k + 1][v] = parent[k][v] < 0 ? -1 : parent[k][parent[k][v]];
            }
        }
    }

    void dfs(int v, int p, int d, ll d2){
        parent[0][v] = p, dep[v] = d, dis[v] = d2;
        for(auto &e : g[v]){
            if(e.first != p) dfs(e.first, v, d + 1, d2 + e.second);
        }
    }

    int lca(int u, int v){
        if(dep[u] > dep[v]) swap(u, v);
        rep(k, 0, lg) {
            if ((dep[v] - dep[u]) >> k & 1) v = parent[k][v];
        }
        if(u == v) return u;
        for (int k = lg - 1; k >= 0; k--) {
            if(parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    ll distance(int a, int b) {
        int ca = lca(a, b);
        return dis[a] + dis[b] - 2 * dis[ca];
    }
};
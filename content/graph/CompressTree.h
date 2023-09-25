/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Time: $O(|S| \log |S|)$
 */


LCA lca(g);
vi vir;
vi stk(n + 1, 0);

auto add_edge = [&](int u, int v, int w) {
    w = lca.distance(u, v);
    g2[u].push_back({v, w});
    g2[v].push_back({u, w});
};
auto build_virtual_tree = [&](vi S) {
    for(auto u : vir) g2[u].clear();
    vir.clear();
    vi S;
    sort(all(S), [&](int u,int v) {return lca.time[u] < lca.time[v];});
    S.resize(unique(all(S)) - S.begin());
    int sz = 0;
    stk[++sz] = 0;
    for(auto u : S) {
        int x = lca.query(u, stk[sz]);
        vir.push_back(u); vir.push_back(x);
        if(u == stk[sz]) continue;
        if(x != stk[sz]) {
            while(sz >= 2 && lca.dep[stk[sz-1]] >= lca.dep[x]) {
                add_edge(stk[sz-1], stk[sz]);
                sz--;
            }
            if(x != stk[sz]) {
                add_edge(x, stk[sz]);
                stk[sz] = x;
            }
        }
        stk[++sz] = u;
    }
    for(int i=1;i<=sz-1;i++) add_edge(stk[i], stk[i+1]);
};

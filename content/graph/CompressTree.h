/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Time: $O(|S| \log |S|)$
 */
LCA lca(g);
graph vt(n);
vi vers;
auto build = [&](vi vs) {
    for (int x : vers) vt[x].clear();
    vers.clear();
    
    sort(all(vs), [&](int i, int j) {return lca.time[i] < lca.time[j];});
    vi a = vs;
    rep(i, 0, sz(vs) - 1) a.push_back(lca.lca(vs[i], vs[i + 1]));
    sort(all(a), [&](int i, int j) {return lca.time[i] < lca.time[j];});
    a.resize(unique(all(a)) - a.begin());
    for (int x : a) vers.push_back(x);
    rep(i, 0, sz(a) - 1) {
        int ca = lca.lca(a[i], a[i + 1]);
        add_edge(ca, a[i + 1]);
    }
};
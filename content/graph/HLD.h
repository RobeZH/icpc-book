/**
 * Author: Johan Sannemo
 * Date: 2015-02-10
 * License: CC0
 * Source: folkore
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 *  edges such that the path from any leaf to the root contains at most log(n)
 *  light edges. The function of the HLD can be changed by modifying T, LOW and
 *  f. f is assumed to be associative and commutative.
 * Usage:
 *  HLD hld(G);
 *  hld.update(index, value);
 *  tie(value, lca) = hld.query(n1, n2);
 * Status: Tested at SPOJ
 */
typedef vector<vi> graph;

struct HLD {
    int n, chainNo, tim;
    Tree tree;
    vi top, din, dout, ord, dep, sub, par;
    graph g;
    HLD(graph &g, int rt = 0): g(g), tree(sz(g)) {
        n = sz(g);
        top = din = dout = ord = dep = sub = par = vi(n);
        chainNo = tim = 0;
        fill(all(din), -1);
        dfs(rt, -1, 0);
        hld(rt, -1, rt);
    }

    void dfs(int v, int p, int d){
        par[v] = p;
        sub[v] = 1;
        dep[v] = d;
        for(int &nxt : g[v]){
            if(nxt == p) continue;
            dfs(nxt, v, d + 1);
            sub[v] += sub[nxt];
            if(g[v][0] == p || sub[nxt] > sub[g[v][0]])
                swap(nxt, g[v][0]);
        }
    }

    void hld(int v, int p, int tp) {
        top[v] = tp;
        din[v] = tim;
        ord[tim++] = v;
        for (auto nxt: g[v]) {
            if (nxt == p) continue;
            if (nxt != g[v][0]) {
                chainNo++; hld(nxt, v, nxt);
            } else hld(nxt, v, tp);
        }
        dout[v] = tim - 1;
    }

    ll query(int a, int b) {
        ll res = 0;
        while(top[a] != top[b]) {
            if(dep[top[a]] < dep[top[b]]) swap(a, b);
            (res += tree.qry(din[top[a]], din[a])) %= mod;
            a = par[top[a]];
        }
        if(din[a] > din[b]) swap(a, b);
        // if querying edge, use tree.qry(din[a] + 1, din[b])
        // lca is variable a
        (res += tree.qry(din[a], din[b])) %= mod; 
        return res;
    }
};

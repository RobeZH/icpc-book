/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: Finding the SCCs of the graph (Kosaraju’s algorithm), cmp is the topo order of the SCCs
 * Time: 
 */
struct SCC {
    vector<vi> G, rG;
    vi vs, used, cmp;
    int n;
    SCC(int n): G(n), rG(n), vs(n), used(n), cmp(n), n(n){}

    void add_edge(int from, int to){
        G[from].push_back(to);
        rG[to].push_back(from);
    }

    void dfs(int v){
        used[v] = true;
        for(int nxt : G[v]) if(!used[nxt]) dfs(nxt);
        vs.push_back(v);
    }

    void rdfs(int v, int k){
        used[v] = true;
        cmp[v] = k;
        for(int nxt : rG[v]) if(!used[nxt]) rdfs(nxt, k);
    }

    int scc(){
        fill(all(used), 0);
        vs.clear();
        rep(v, 0, n) if(!used[v]) dfs(v);
        fill(all(used), 0);
        int k = 0;
        reverse(all(vs));
        for(int v : vs) if(!used[v]) rdfs(v, k++);
        return k;
    }
};

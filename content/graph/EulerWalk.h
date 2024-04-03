/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: store the **reverse path** in the graph!!! 
 * Time:
 */

struct Euler {
    struct edge {
        // c is orientation of the edge
        int to, id, c;
    };
    vector<vector<edge>> G;
    vi pt, evis, path;
    Euler(int n, int m): G(n), pt(n, 0), evis(m, 0){};


    void add_edge(int u, int v, int eid) {
        G[u].push_back({v, eid, 0});
        G[v].push_back({u, eid, 1});
    }

    void dfs(int v){
        int &i = pt[v];
        while(true){
            while(i < sz(G[v]) && evis[G[v][i].id]) i++; if(i == sz(G[v])) break;
            auto e = G[v][i++];
            evis[e.id] = 1;
            dfs(e.to);
            // record the result
            res[e.id] = e.c;
            path.push_back(v);
        }
    }

    void get_path() {
        rep(i, 0, sz(G)) {
            if(pt[i] < sz(G[i])) {
                dfs(i);
            }
        }          
    }
};
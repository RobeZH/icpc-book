/**
  	* Author: 
    * Date: 
    * License: CC0
    * Source: 
    * Description: 1-indexed general matching
 * Time: O(NM), faster in practice
 */

struct MaxMatch {
    vi vis, par, orig, match, aux;
    int t, N;
    vector<vi> adj;
    queue<int> Q;

    MaxMatch(int n): vis(n + 1), par(n + 1), orig(n + 1), match(n + 1), aux(n + 1), adj(n + 1), t(0), N(n) {}


    void addEdge(int u, int v) {
        assert(u && v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void augment(int u, int v) {
        int pv = v, nv;
        do {
            pv = par[v]; nv = match[pv];
            match[v] = pv; match[pv] = v;
            v = nv;
        } while(u != pv);
    }

    int lca(int v, int w) {
        ++t;
        while (1) {
            if (v) {
                if (aux[v] == t) return v; aux[v] = t;
                v = orig[par[match[v]]];
            }
            swap(v, w);
        }
    }

    void blossom(int v, int w, int a) {
        while (orig[v] != a) {
            par[v] = w; w = match[v];
            if (vis[w] == 1) Q.push(w), vis[w] = 0;
            orig[v] = orig[w] = a;
            v = par[w];
        }
    }

    bool bfs(int u) {
        fill(vis.begin()+1, vis.begin()+1+N, -1);
        iota(orig.begin() + 1, orig.begin() + N + 1, 1);
        Q = queue<int> (); Q.push(u); vis[u] = 0;
        while (sz(Q)) {
            int v = Q.front(); Q.pop();
            trav(x,adj[v]) {
                if (vis[x] == -1) {
                    par[x] = v; vis[x] = 1;
                    if (!match[x]) return augment(u, x), true;
                    Q.push(match[x]); vis[match[x]] = 0;
                } else if (vis[x] == 0 && orig[v] != orig[x]) {
                    int a = lca(orig[v], orig[x]);
                    blossom(x, v, a); blossom(v, x, a);
                }
            }
        }
        return false;
    }

    int Match() {
        int ans = 0;
        // find random matching (not necessary, constant improvement)
        vi V(N-1); iota(all(V), 1);
        shuffle(all(V), mt19937(233333));
        trav(x,V) if(!match[x])
            trav(y,adj[x]) if (!match[y]) {
            match[x] = y, match[y] = x;
            ++ans; break;
        }

        rep(i,1,N+1) if (!match[i] && bfs(i)) ++ans;
        return ans;
    }
};
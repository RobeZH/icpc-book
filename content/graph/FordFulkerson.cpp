/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Time: 
 */

struct Flow {
    struct edge{
        int to, cap, rev;
        edge(int _to, int _cap, int _rev){
            to = _to, cap = _cap, rev = _rev;
        }
    };

    vector<vector<edge>> G;
    vector<int> used;
    Flow(int n): G(n), used(n) {}


    void add_edge(int from, int to, int cap){
        G[from].push_back(edge(to, cap, G[to].size()));
        G[to].push_back(edge(from, 0, G[from].size() - 1));
    }

    int dfs(int v, int t, int f){
        if(v == t) return f;
        used[v] = true;

        for(int i = 0; i < G[v].size(); i++){
            edge &e = G[v][i];
            if(!used[e.to] && e.cap > 0){
                int d = dfs(e.to, t, min(e.cap, f));
                if(d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t){
        int f = 0;
        for(;;){
            fill(used.begin(), used.end(), 0);
            int d = dfs(s, t, INF);
            if(d == 0) return f;
            f += d;
        }
    }
};
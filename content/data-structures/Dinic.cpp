/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Time: 
 */

struct edge{
    int to, cap, rev;
    edge(int _to, int _cap, int _rev){
        to = _to, cap = _cap, rev = _rev;
    }
};

struct Dinic {
    vector<vector<edge>> G;
    vi level, iter;
 
    Dinic(int n) : G(n), level(n), iter(n) {}
 
    void add_edge(int from, int to, int cap, int id) {
        G[from].push_back(edge(to, cap, G[to].size(), id));
        G[to].push_back(edge(from, 0, G[from].size() - 1, id));
    }
 
    void bfs(int s) {
        fill(all(level), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int i = 0; i < G[v].size(); i++) {
                edge &e = G[v][i];
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }
 
 
    int dfs(int v, int t, int f) {
        if (v == t) return f;
 
        for (int &i = iter[v]; i < G[v].size(); i++) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(e.cap, f));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
 
 
    int max_flow(int s, int t) {
        int flow = 0;
        for (;;) {
            bfs(s);
            if (level[t] < 0) return flow;
            fill(all(iter), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
    }
};
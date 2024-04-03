/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: $T$ is the block-cut tree, node $n + i$ is the $i$-th vertex BCC, $bcc$ contains all the edge ids (no duplicates) within a BCC (need to uncomment S2).
 * Time: $O(E + V)$
 */
struct Tarjan {
    vi low, pre;
    int tim = 0, ccnt = 0;
    vector<vi> bcc, T;
    stack<int> S; // , S2;
    graph &g;

    Tarjan(int n, graph &g): g(g), low(n), pre(n), bcc(n * 2), T(2 * n), ccnt(n) {}

    void dfs(int v, int par) {
        low[v] = pre[v] = ++tim;
        S.push(v);
        for(auto e : g[v]) {
            if(e.to == par) continue;
            if(!pre[e.to]) {
//                S2.push(e.id);
                dfs(e.to, v);
                low[v] = min(low[v], low[e.to]);
                if(low[e.to] >= pre[v]) {
                    int cur;
                    do {
                        cur = S.top();
                        S.pop();
                        T[ccnt].push_back(cur);
                        T[cur].push_back(ccnt);
                    } while(cur != e.to);
//                    do {
//                        cur = S2.top();
//                        S2.pop();
//                        bcc[ccnt].push_back(cur);
//                    } while(cur != e.id);
                    T[ccnt].push_back(v);
                    T[v].push_back(ccnt);
                    ccnt++;
                }
            }
            else if(pre[e.to] < pre[v]) {
//                S2.push(e.id);
                low[v] = min(low[v], pre[e.to]);
            }
        }
    }
};
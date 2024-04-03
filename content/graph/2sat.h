/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Time: 
 */

struct SAT {
    SCC scc;
    int nvars;
    SAT (int nvars): scc(nvars * 2), nvars(nvars) {
    }
    void add(int a, int x, int b, int y) {
        scc.add_edge(a + x * nvars, b + y * nvars);
        scc.add_edge(b + (!y) * nvars, a + (!x) * nvars);
    }

    void equiv(int a, int b) {
        add(a, 1, b, 1);
        add(a, 0, b, 0);
    }

    bool solve() {
        scc.scc();
        rep(i, 0, nvars) {
            if(scc.cmp[i] == scc.cmp[i + nvars]) return false;
        }
        return true;
    }
};
/**
 * Author: 
 * Date: 
 * License:
 * Source: 
 * Description: sparse table for range minimum
 * Time: 
 */

struct RMQ {
    vector<vi> st;
    vi mm;
 
    RMQ(vi &x) {
        int n = sz(x);
        mm.resize(n + 1);
        mm[0] = -1;
        rep(i, 1, n + 1) mm[i]= (i & (i-1)) == 0 ? mm[i-1] + 1 : mm[i-1];
        int LG = 0;
        while((1 << LG) <= n) LG++;
        st.resize(LG, vi(n));
        rep(i, 0, n) st[0][i] = x[i];
        for(int lg = 1; lg < LG; lg++){
            for(int j = 0; j + (1 << lg) - 1 < n; j++) {
                st[lg][j] = min(st[lg - 1][j], st[lg - 1][j + (1 << (lg - 1))]);
            }
        }
    }

    int rmq(int l, int r) {
        int k = mm[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Time: Both operations are $O(\log N)$.
 */
struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) { // a[pos] += dif
        for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll get(int pos) { // sum of values in [0, pos]
        ll res = 0;
        for (; pos >= 0; pos = (pos & (pos + 1)) - 1) res += s[pos];
        return res;
    }
};



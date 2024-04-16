/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: f[i]: the longest smaller prefix that is a suffix of t[1...i] (in length), one-index. f("bacba") = [0, 0, 0, 0, 1, 2]
 * Time: O(|t| + |s|)
 */


struct KMP {
    vi f;
    string t;

    KMP(string t): t(t) {
        calc_next(t);
    }

    void calc_next(string t) {
        f.resize(sz(t) + 1);
        f[0] = 0; f[1] = 0;
        for(int i = 1; i < sz(t); i++){
            int j = f[i];
            while(j && t[i] != t[j]) j = f[j];
            f[i+1] = t[i] == t[j] ? j + 1 : 0;
        }
    }

    int match(string s) {
        int n = sz(s), m = sz(t);
        int res = 0, j = 0;
        for(int i = 0; i < n; i++){
            while(j && t[j] != s[i]) j = f[j];
            if(t[j] == s[i]) j++;
            if(j == m) res ++, j = f[j];
        }
        return res;
    }
};
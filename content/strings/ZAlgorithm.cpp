/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: str = "aabaacd", z  = {7, 1, 0, 2, 1, 0, 0}
 * Time: 
 */
vi get_z(string str) {
    int n = sz(str);
    vi z(n);
    z[0] = n;
    for(int i = 1, l = 0, r = 0; i < n; ++i){
        if(i <= r) z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < n && str[z[i]] == str[i + z[i]]) ++z[i];
        if(i + z[i] - 1 > r) l = i,  r = i + z[i] - 1;
    }
    return z;
}
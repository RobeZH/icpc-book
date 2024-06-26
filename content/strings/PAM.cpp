/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Time: 
 */

const int mod = (int)1e9 + 7;
struct PAM {
    static const int N = (int) 1e6 + 50;
    int s[N], now;
    int nxt[N][26], fail[N], l[N], last, tot;
    int diff[N], anc[N];
    int ans[N], dp[N];
	void clear() { /// start-hash
		s[0] = l[1] = -1; 
		fail[0]=tot=now=1; 
		last=l[0]=0;
		memset(nxt[0], -1, sizeof nxt[0]);
		memset(nxt[1], -1, sizeof nxt[1]);
	}

	PAM() { clear(); }

	int newnode(int len) {
	    tot++;
		memset(nxt[tot], -1, sizeof nxt[tot]);
	    fail[tot] = 0;
	    l[tot] = len;
	    return tot;
	}

	int get_fail(int x) {
		while (s[now - l[x] - 2] != s[now - 1])x = fail[x];
	    return x;
	}

	void add(int ch) {
	    s[now++] = ch;
	    int cur = get_fail(last);
	    if (nxt[cur][ch] == -1) {
	        int tt = newnode(l[cur] + 2);
	        fail[tt] = nxt[get_fail(fail[cur])][ch];
	        if(fail[tt] == -1) fail[tt] = 0;
	       	nxt[cur][ch] = tt;
       	    diff[tt] = l[tt] - l[fail[tt]];
       	    anc[tt] = diff[tt] == diff[fail[tt]] ? anc[fail[tt]] : fail[tt];
       	}
		last = nxt[cur][ch];
	}  /// end-hash
	void trans(int i) { // start-hash
	for(int p = last; p > 1; p = anc[p]) {
	            dp[p] = ans[i - l[anc[p]] - diff[p]];
	            if(diff[p] == diff[fail[p]]) {
	                (dp[p] += dp[fail[p]]) %= mod;
	            }
	            (ans[i] += (i % 2 == 0) * dp[p]) %= mod;
	        }
	} /// end-hash
} pam;
/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: Build suffix automaton in $O(nB)$. For multi-string SAM, build a trie and do BFS, and set last as the last of parent in the trie.n the trie.
 * Time: 
 */

struct state {
    int len, link;
    int next[B];
};

struct SAM {
    state st[MAXLEN * 2];
    int sz, last;
    int cnt[MAXLEN * 2];

    void sam_init() { /// start-hash
        st[0].len = 0;
        st[0].link = -1;
        memset(st[0].next, -1, sizeof(st[0].next));
        sz = 1;
        last = 0;
    } /// end-hash

    void sam_extend(int c) { /// start-hash
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        memset(st[cur].next, -1, sizeof(st[cur].next));
        int p = last;
        while(p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if(p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if(st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
                st[clone].link = st[q].link;
                while(p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    } /// end-hash

} sam;

/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description:  
 * Time: Init, and insert strings, and then build. Remember to propagate information to from fail link.
 */
const int M = (int)5e5 + 500;

struct Trie {
    static const int B = 26;
    int next[M][B], fail[M], end[M];
    int root, L;

    int newnode() {
        rep(i, 0, B) next[L][i] = -1;
        end[L++] = 0;
        return L - 1;
    }

    void init() { // Please do initalize it!!
        L = 0;
        root = newnode();
    }

   void insert(const string &buf) {
        int len = sz(buf);
        int now = root;
        rep(i, 0, len) {
            int &nxt = next[now][buf[i] - 'a'];
            if(nxt == -1) nxt = newnode();
            now = nxt;
        }
        end[now] = 1;
    }

    void build() {
        queue<int> Q;
        fail[root] = root;
        rep(i, 0, B) {
            if (next[root][i] == -1) next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            rep(i, 0, B) {
                if (next[now][i] == -1) next[now][i] = next[fail[now]][i];
                else{
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
            }
        }
    }
}Aho;
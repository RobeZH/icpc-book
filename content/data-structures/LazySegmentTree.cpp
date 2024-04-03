/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Time: 
 */

#define lson(x) x * 2 + 1
#define rson(x) x * 2 + 2

struct node {
    ll sum, add;

    void add_val(ll x, ll len) {
        (add += x) %= mod;
        (sum += len * x) %= mod;
    }

    void merge(node &ls, node &rs) {
        sum = (ls.sum + rs.sum) % mod;
    }
};

struct Tree {
    int n;
    vector<node> dat;
    Tree(int n): dat(n * 4), n(n) {}

    void push_down(int x, int l, int r) {
        if(dat[x].add) {
            if(l < r) {
                int mid = (r + l) / 2;
                dat[lson(x)].add_val(dat[x].add, mid - l + 1);
                dat[rson(x)].add_val(dat[x].add, r - mid);
            }
            dat[x].add = 0;
        }
    }

    void init(int x, int l, int r, vi &a) {
        if(l == r) {
            dat[x].sum = a[l] % mod, dat[x].add = 0;
            return ;
        }
        int mid = (l + r) / 2;
        init(lson(x), l, mid, a);
        init(rson(x), mid + 1, r, a);
        dat[x].add = 0;
        dat[x].merge(dat[lson(x)], dat[rson(x)]);
    }

    ll query(int a, int b, int x, int l, int r) {
        int mid = (l + r) / 2;
        if(r < a || l > b) return 0;
        push_down(x, l, r);
        if(l >= a && r <= b) return dat[x].sum;
        return (query(a, b, lson(x), l, mid) + query(a, b, rson(x), mid+1, r)) % mod;
    }

    void update(int a, int b, int x, int l, int r, int delta) {
        int mid = (l + r) / 2;
        if(r < a || l > b) return ;
        push_down(x, l, r);
        if(l >= a && r <= b) {
            dat[x].add_val(delta, r - l + 1);
            return ;
        }
        update(a, b, lson(x), l, mid, delta);
        update(a, b, rson(x), mid+1, r, delta);
        dat[x].merge(dat[lson(x)], dat[rson(x)]);
    }

    ll qry(int a, int b) {
        return query(a, b, 0, 0, n - 1);
    }
    void upd(int a, int b, int d) {
        update(a, b, 0, 0, n - 1, d);
    }
} ;



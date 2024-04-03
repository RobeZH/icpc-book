/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: 
 * Time: 
 */
#define lson(x) 2*x+1
#define rson(x) 2*x+2

struct node {
    ll sum;
    void add(int val) {
        sum += val;
    }
};

node merge(node L, node R) {
    return {L.sum + R.sum};
}

struct Tree {
    int n;
    vector<node> dat;
    Tree(int n): dat(n * 4) {}
    void init(int x, int l, int r, vi &a) {
        if(l == r) {dat[x] = {a[l]}; return ;}
        int mid = (l + r) / 2;
        init(lson(x), l, mid, a);
        init(rson(x), mid + 1, r, a);
        dat[x] = merge(dat[lson(x)], dat[rson(x)]);
    }
    void update(int pos, int x, int l, int r, int val) {
        if(l == r) {dat[x].add(val); return ;}
        int mid = (l + r) / 2;
        if(pos <= mid) update(pos, lson(x), l, mid, val);
        else update(pos, rson(x), mid + 1, r, val);
        dat[x] = merge(dat[lson(x)], dat[rson(x)]);
    }
    node query(int a, int b, int x, int l, int r) {
        if(r < a || b < l) return {0};
        int mid = (l + r) / 2;
        if(a <= l && r <= b) return dat[x];
        else return merge(query(a, b, lson(x), l, mid),
                          query(a, b, rson(x), mid + 1, r));
    }
};
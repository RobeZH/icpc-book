/**
 * Author: 
 * Date: 
 * Licedate: CC0
 * Source: 
 * Description: 
 * Time:
 */

#define lson(x) dat[x].ls
#define rson(x) dat[x].rs

struct PST {
    int ncnt = 1; //Need to initialize before every test case!

    struct node{
        int ls, rs, sum;
    } dat[N * 30];

    int leaf(int val){
        dat[ncnt].ls = dat[ncnt].rs = 0;
        dat[ncnt].sum = val;
        return ncnt++;
    }

    int combine(int ls, int rs) {
        lson(ncnt) = ls;
        rson(ncnt) = rs;
        dat[ncnt].sum = (ls ? dat[ls].sum : 0) + (rs ? dat[rs].sum : 0);
        return ncnt++;
    }

    int n;

    int build(int a[], int tl = 0, int tr = n-1){
        if(tl == tr) return leaf(a[tl]);
        int mid = (tl + tr) / 2;
        return combine(build(a, tl, mid), build(a, mid + 1, tr));
    }

    int get_sum(int v, int l, int r, int tl = 0, int tr = n-1){
        if(tr < l || tl > r) return 0;
        if(l <= tl && tr <= r) return dat[v].sum;
        int tm = (tl + tr) / 2;

        return get_sum(lson(v), l, r, tl, tm)
               + get_sum(rson(v), l, r, tm + 1, tr);
    }

    int update(int v, int pos, int tl = 0, int tr = n - 1){
        if(tl == tr) return leaf(dat[v].sum + 1);
        int tm = (tl + tr) / 2;
        if(pos <= tm) return combine(update(lson(v), pos, tl, tm), rson(v));
        else return combine(lson(v), update(rson(v), pos, tm+1, tr));
    }
}
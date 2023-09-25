/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: Iterative SegTree
 * Time: 
 */
int n;
node t[2 * N];

void build() {  // build the tree
    for (int i = n; i < 2 * n; i++) t[i] = a[i];
    for (int i = n - 1; i > 0; --i) t[i] = combine(t[i<<1], t[i<<1|1]);
}

void modify(int p, const S& value) {
  for (t[p += n] = value; p >>= 1; ) t[p] = combine(t[p<<1], t[p<<1|1]);
}

S query(int l, int r) {
  S resl, resr;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) resl = combine(resl, t[l++]);
    if (r&1) resr = combine(t[--r], resr);
  }
  return combine(resl, resr);
}
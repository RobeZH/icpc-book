
/**
 * Author: 
 * Date: 
 * License:
 * Source: 
 * Description: Split-Merge Treap. Make sure to visit value after all the tags are pushed down!
 * Time: 
 */


mt19937 rng(23333);  /// start-hash
struct Node {
	Node *l = 0, *r = 0;
	int y, c = 1; // y: random key
	pii v; // in case of duplicate key, use pair.
	int add; // int par; if wants to keep the parent, update every time parent-child relationship, changes.
    Node(int v, int idx) : y(rng()), v({v, idx}), add(0) {
    }
    void recalc();
    void push_down();
};

int cnt(Node* n) {return n ? n->c : 0;}
void Node::recalc() {c = cnt(l) + cnt(r) + 1;}

void add_val(Node* n, int val) {
    if(!n) return ;
    n->add += val;
    n->v.first += val;
}

void Node::push_down() {
    if(add) {
        add_val(l, add);
        add_val(r, add);
        add = 0;
	} 
}

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	n->push_down();
	if (cnt(n->l) >= k) { // "n->val >= v" for lower_bound(v)
		auto pa = split(n->l, k); 
		n->l = pa.second; 
		n->recalc();
		return {pa.first, n};
    } else {
        auto pa = split(n->r, k - cnt(n->l) - 1);
        n->r = pa.first;
        n->recalc();
        return {n, pa.second};
	} 
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    l->push_down();
    r->push_down();

    if(l->y > r->y) {
    	l->r = merge(l->r, r);
    	l->recalc();
    	return l;
    } else {
    	r->l = merge(l, r->l);
    	r->recalc();
    	return r;
    }
}

Node* ins(Node* t, Node* n, int pos) {
    auto pa = split(t, pos);
    return merge(merge(pa.first, n), pa.second);
} /// end-hash

/// start-hash
Node* del(Node* t, int pos) { 
    auto pa = split(t, pos);
    auto pb = split(pa.second, 1);
    return merge(pa.first, pb.second);
}
Node* find(Node *cur, int k) {
    if(!cur) return 0;
    if(cnt(cur->l) > k) return find(cur->l, k);
    else if(cnt(cur -> l) == k) return cur;
    else return find(cur->r, k - cnt(cur->l) - 1);
}
typedef pair<Node*, int> pni;
pni lower_bound(Node *cur, pii v, int pos) { // return {the Node*, position}; {NULL, n} in case of .end()
    if(!cur) return {0, pos};
    cur->push_down();
    if(cur->v >= v) {
        auto res = lower_bound(cur->l, v, pos);
        if(res.first) return res;
        else return {cur, pos + cnt(cur->l)};
	} else return lower_bound(cur->r, v, pos + cnt(cur->l) + 1);
} /// end-hash
/**
 * Author: 
 * Date: 
 * License: CC0
 * Source: 
 * Description: Finding a tree where the min edge on the path from a to b is the min a-b-cut. Complexity: O(n * c(max flow))
 * Time: 
 */

struct GomoryHu {
    vector<pair<pii, ll>> ed;
    void ae(ll a, ll b, ll c) { ed.push_back({{a, b}, c});}
	vector<pair<pii, ll>> init(ll N) {
        vector<pii> ret(N + 1, {0, 0});
        rep(i, 1, N) {
            Dinic D(N);
            trav(t, ed) D.add_edge(t.first.first, t.first.second, t.second), 
            		D.add_edge(t.first.second, t.first.first, t.second); 
    		ret[i].second = D.max_flow(i, ret[i].first);
			rep(j, i + 1, N) if (ret[j].first == ret[i].first && D.level[j] >= 0) ret[j].first = i;
        }
        vector<pair<pii, ll>> res;
        rep(i, 1, N) res.push_back({{i, ret[i].first}, ret[i].second}); 
        return res;
	}
}; 
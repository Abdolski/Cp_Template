//
// Created by expert on 12/2/2025.
//
#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define ll long long
#define pb(n) push_back(n)
#define F first
#define S second
#define vi vector<int>
#define vl vector<ll>
#define mp(x, y) make_pair(x, y)
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
#define all(x) x.begin(), x.end()
#define f(i,x,n) for(int i = x; i < n; i++)
using pll = pair<ll, ll>;
const ll sup = 1e18;
const ll inf = -1e18;
const ll mod = 1e9 + 7;
const ll MOD = 998244353;
const ll dcinq=1e5+5;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }


const ll N = 1e5+7;
vector<bool> is_prime(N+1, true);
vector<ll> primessss;
void seive() {
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primessss.push_back(i);
        }
        if (is_prime[i] && (long long)i * i <=N) {
            for (ll j = i * i; j <= N; j += i)
                is_prime[j] = false;
        }
    }
}
long long bin_po(long long base, long long exp) {
    long long result = 1;
    base = base ;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) ;
        }
        base = (base * base) ;
        exp /= 2;
    }

    return result;
}

ll dirx[4]={1,1,2,2};
ll diry[4]={1,2,1,2};



long long mod_pow(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

long long mod_inverse(long long a, long long m = mod) {
    return mod_pow(a, m - 2, m); // Only if m is prime
}

bool isPerfectCube(int n) {
    int root = round(cbrt(n));
    return root * root * root == n;
}

map<int, int> prime_factors(int n) {
    map<int, int> factors;

    // Handle 2 separately
    while (n % 2 == 0) {
        factors[2]++;
        n /= 2;
    }

    // Handle odd factors
    for (int p = 3; p * p <= n; p += 2) {
        while (n % p == 0) {
            factors[p]++;
            n /= p;
        }
    }

    // If n is a prime > sqrt(n)
    if (n > 1) {
        factors[n]++;
    }

    return factors;
}
bool prime(ll n) {
    if (n<=1) return false;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}
//int lcm(int a, int b) {return a * b / __gcd(a, b);}



//TRIE XOR
/*
 *#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Maximum number of bits needed for 10^18 (~2^60). We use 60 bits (0 to 59).
const int MAX_BITS = 60;

// --- Trie Node Structure ---
struct TrieNode {
    // children[0] for bit 0, children[1] for bit 1
    TrieNode* children[2];
    // Count of numbers in the multiset that pass through this node
    long long count;

    TrieNode() : count(0) {
        children[0] = children[1] = nullptr;
    }

    // Destructor to clean up memory
    ~TrieNode() {
        delete children[0];
        delete children[1];
    }
};

// --- Trie Operations ---

// Inserts a number x into the trie (Type 0: Add a book)
void insert(TrieNode* root, long long x) {
    TrieNode* curr = root;
    for (int i = MAX_BITS - 1; i >= 0; --i) {
        // Get the i-th bit of x
        int bit = (x >> i) & 1;

        if (curr->children[bit] == nullptr) {
            curr->children[bit] = new TrieNode();
        }

        curr = curr->children[bit];
        curr->count++; // Increment count for the prefix
    }
}

// Removes a number x from the trie (Type 1: Remove a book)
void remove(TrieNode* root, long long x) {
    TrieNode* curr = root;
    // Guaranteed that x exists, so no need to check for nullptr children
    for (int i = MAX_BITS - 1; i >= 0; --i) {
        int bit = (x >> i) & 1;

        curr = curr->children[bit];
        curr->count--; // Decrement count for the prefix
        // Note: We don't explicitly prune nodes here,
        // relying on the count to manage the multiset size.
    }
}

// Handles Type 2 query: Count x in S where x ^ y > z
long long query(TrieNode* root, long long y, long long z) {
    long long total_count = 0;
    TrieNode* curr = root;

    for (int i = MAX_BITS - 1; i >= 0; --i) {
        if (curr == nullptr) {
            break; // No more numbers in this branch
        }

        int y_i = (y >> i) & 1;
        int z_i = (z >> i) & 1;

        // Determine the two possible choices for x_i (0 and 1)

        // Iterate over the two children of the current node
        for (int x_i = 0; x_i <= 1; ++x_i) {
            TrieNode* child = curr->children[x_i];
            if (child == nullptr) {
                continue;
            }

            int r_i = x_i ^ y_i; // The resulting XOR bit (r = x ^ y)

            if (r_i > z_i) {
                // Case 1: r_i = 1 and z_i = 0. This guarantees x ^ y > z.
                // Add all numbers in this subtree to the total count.
                total_count += child->count;

            } else if (r_i == z_i) {
                // Case 2: r_i = z_i (0=0 or 1=1). Tie continues.
                // If this is the path that maintains the tie (r_i = z_i),
                // we must move 'curr' to this child to continue the tie-breaking
                // in the next iteration.

                // IMPORTANT: Since we are iterating over both x_i=0 and x_i=1,
                // we must only update 'curr' for the branch that keeps the tie,
                // and skip the other branch (r_i < z_i).

                // If r_i == z_i, we want to follow this path.
                // We will handle the tie-continuation logic outside this loop
                // to avoid double-assignment of 'curr'.

            } else { // r_i < z_i (r_i = 0 and z_i = 1)
                // Case 3: This branch guarantees x ^ y < z. Ignore it.
            }
        }

        // --- Tie Continuation Logic ---
        // Find the one path (if it exists) that continues the tie: r_i = z_i
        int x_i_for_tie = z_i ^ y_i; // The bit x_i that results in r_i = z_i

        // Move to the child that continues the tie (0 = 0 or 1 = 1)
        curr = curr->children[x_i_for_tie];

        // If the path that continues the tie doesn't exist, we stop.
        if (curr == nullptr) {
            break;
        }
    }

    return total_count;
}

// --- Main Function ---
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    // The root node of the Trie
    TrieNode* root = new TrieNode();

    for (int k = 0; k < q; ++k) {
        int type;
        if (!(cin >> type)) break;

        if (type == 0) {
            // Type 0: Add book x
            long long x;
            cin >> x;
            insert(root, x);
        } else if (type == 1) {
            // Type 1: Remove book x
            long long x;
            cin >> x;
            remove(root, x);
        } else if (type == 2) {
            // Type 2: Query x ^ y > z
            long long y, z;
            cin >> y >> z;
            cout << query(root, y, z) << "\n";
        }
    }

    // Clean up memory
    delete root;

    return 0;
}
 */


//____________________________________________________________________________

//TRAJAN ALGO
/*
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> disc, low, st, inStack, comp;
int timer = 0, scc_id = 0;

void tarjan(int u) {
    disc[u] = low[u] = ++timer;
    st.push_back(u);
    inStack[u] = 1;

    for (int v : g[u]) {
        if (!disc[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (disc[u] == low[u]) {
        // root of SCC
        while (true) {
            int v = st.back(); st.pop_back();
            inStack[v] = 0;
            comp[v] = scc_id;
            if (v == u) break;
        }
        scc_id++;
    }
}
////////////////
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    g.assign(n+1, {});
    disc.assign(n+1, 0);
    low.assign(n+1, 0);
    inStack.assign(n+1, 0);
    comp.assign(n+1, -1);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; i++)
        if (!disc[i]) tarjan(i);

    cout << "Number of SCCs = " << scc_id << "\n";
    for (int i = 1; i <= n; i++)
        cout << "Node " << i << " in comp " << comp[i] << "\n";
}

*/
//____________________________________________________________________________
//BELLMAN FORD
// struct Edge {
//     int from, to;
//     ll weight;
// };
//
// const int MAXN = 2505;
//
// int n, m, parent[MAXN];
// ll dist[MAXN];
// vector<Edge> graph;
//
// void bellman_ford(int source) {
//     fill(parent + 1, parent + n + 1, 0);
//     fill(dist + 1, dist + n + 1, 1e18);
//     dist[source] = 0;
//     int last_node_updated;
//     for (int i = 1; i <= n; i++) {
//         last_node_updated = -1;
//         for (Edge &e : graph) {
//             if (dist[e.from] + e.weight < dist[e.to]) {
//                 dist[e.to] = dist[e.from] + e.weight;
//                 parent[e.to] = e.from;
//                 last_node_updated = e.to;
//             }
//         }
//     }
//     //
//     // vector<int> cycle;
//     // for (int i = 0; i < n - 1; i++) {
//     //     last_node_updated = parent[last_node_updated];
//     // }
//     // for (int x = last_node_updated;; x = parent[x]) {
//     //     cycle.push_back(x);
//     //     if (x == last_node_updated && cycle.size() > 1) break;
//     // }
//     // reverse(cycle.begin(), cycle.end());
//     // for (int x : cycle) cout << x << ' ';
//     // cout << '\n';
//
// }
/*

vector<long long> deg;
vector<long long> ans;

bool topological_sort(const vector<vector<long long>>& adj) {
    int n = adj.size() - 1;

    queue<long long> q;
    ans.clear();
    ans.reserve(n);

    // push all nodes with 0 indegree
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        long long u = q.front();
        q.pop();
        ans.push_back(u);

        for (long long v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) q.push(v);
        }
    }

    // Kahn cycle check
    return (int)ans.size() == n;
}
*/
//-----------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//DSU WITH ROLLBACK
class Rollback_DSU {
private:
    vector<int> p, sz;
    // stores previous unites
    vector<pair<int &, int>> history;

public:
    Rollback_DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }

    int get(int x) { return x == p[x] ? x : get(p[x]); }

    void unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) { return; }
        if (sz[a] < sz[b]) { swap(a, b); }

        // save this unite operation
        history.push_back({sz[a], sz[a]});
        history.push_back({p[b], p[b]});

        p[b] = a;
        sz[a] += sz[b];
    }

    int snapshot() { return history.size(); }

    void rollback(int until) {
        while (snapshot() > until) {
            history.back().first = history.back().second;
            history.pop_back();
        }
    }
};
//-----------------------------------------------------------------------------------------------------
struct UnionFind {
    std::vector<int> parent, sz;
    int components;


    UnionFind(int n) {

        parent.resize(n);

        sz.resize(n, 1);
        components = n;
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // Path-compressed find
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }
    int finddepth(int u) {
        if (parent[u] == u) return 0;
        return 1 + finddepth(parent[u]);
    }

    // Union by size
    bool unite(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) return false;


        if (sz[u] < sz[v]) {
            parent[u] = v;
            sz[v] += sz[u];
        } else {
            parent[v] = u;
            sz[u] += sz[v];
        }
        components--;
        return true;
    }

    bool connected(int u, int v) {
        return find(u) == find(v);
    }

    int componentSize(int u) {
        return sz[find(u)];
    }

    int count() {
        return components;
    }
};
/*
void Prim(ll n, vector<vector<pair<ll,ll>>> adj) {
    ll m=n-1;
    ll mstcost=0;
    ll mstindex=0;
    vl mstedges(n,0);
    vl vistied(n+1,0);
    auto cmp = [](const array<ll,3>& a, const array<ll,3>& b) {
        return a[2] > b[2];
    };
    priority_queue<array<ll, 3>, vector<array<ll, 3>>,decltype(cmp)> pq(cmp);
    pq.push({1,1,0});
    while (!pq.empty()) {
        auto [from ,to,cost] = pq.top();
        pq.pop();
        if (vistied[to]) continue;
        vistied[to] = true;
        mstcost += cost;
        mstedges[mstindex++]=to;
        for (auto [tto ,cost] : adj[to]) {
            if (!vistied[tto]) {
                pq.push({to,tto,cost});
            }

        }
    }

    if (mstindex!=n) {
        cout<<-1<<endl;

    }
    else {
        cout<<mstcost<<endl;
    }

}
*/

//-----------------------------------------------------------------------------------------------------
// MERGE SORT SEGTREE
/*
    const int MAXN = 100000;
vector<vector<int>> tree;          // sorted values
vector<vector<unsigned int>> px;   // prefix XOR

int n, q;
int a[MAXN+5];


// Build merge sort tree
void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = {a[l]};
        px[idx] = {a[l]};
        return;
    }
    int mid = (l + r) / 2;
    build(idx*2, l, mid);
    build(idx*2+1, mid+1, r);

    // merge sorted lists
    tree[idx].resize(tree[idx*2].size() + tree[idx*2+1].size());
    merge(tree[idx*2].begin(), tree[idx*2].end(),
          tree[idx*2+1].begin(), tree[idx*2+1].end(),
          tree[idx].begin());

    // prefix XOR
    px[idx].resize(tree[idx].size());
    px[idx][0] = tree[idx][0];
    for (int i = 1; i < (int)tree[idx].size(); i++)
        px[idx][i] = px[idx][i-1] ^ tree[idx][i];
}


// Count numbers <= x in range
int count_le(int idx, int l, int r, int ql, int qr, int x) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) {
        return upper_bound(tree[idx].begin(), tree[idx].end(), x) - tree[idx].begin();
    }
    int mid = (l + r) / 2;
    return count_le(idx*2, l, mid, ql, qr, x)
         + count_le(idx*2+1, mid+1, r, ql, qr, x);
}


// XOR of all values <= x in range
unsigned int xor_le(int idx, int l, int r, int ql, int qr, int x) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) {
        int pos = upper_bound(tree[idx].begin(), tree[idx].end(), x) - tree[idx].begin();
        if (pos == 0) return 0;
        return px[idx][pos - 1];
    }
    int mid = (l + r) / 2;
    return xor_le(idx*2, l, mid, ql, qr, x)
         ^ xor_le(idx*2+1, mid+1, r, ql, qr, x);
}


// Find K-th smallest in range
int kth_smallest(int l, int r, int k) {
    int lo = 0, hi = (1<<30);
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (count_le(1, 1, n, l, r, mid) >= k)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}


void solvit() {

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    tree.resize(4*n);
    px.resize(4*n);

    build(1, 1, n);

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;

        int len = r - l + 1;
        k = min(k, len);

        // find k-th smallest value
        int val = kth_smallest(l, r, k);

        // how many < val?
        int less_cnt = count_le(1, 1, n, l, r, val - 1);
        unsigned int ans = xor_le(1, 1, n, l, r, val - 1);

        // how many = val we need?
        int need = k - less_cnt;

        // XOR val 'need' times
        if (need % 2 == 1) ans ^= val;

        cout << ans << "\n";
    }


}

*/


vector<ll> fac(N, 1);
vector<ll> inve(N,1);

int inv(int a) {
    return a <= 1 ? a : MOD - (long long) (MOD / a) * inv(MOD % a) % MOD;
}
void preproc() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }
    inve[0]=1;
    inve[N-1]=inv(fac[N-1]);
    for(int i=N-2;i>0;i--){
        inve[i]=((i+1)*inve[i+1])%MOD;
    }
}

ll C(ll n, ll k) {
    return (((((fac[n] *inve[n - k])%MOD) * inve[k]) % MOD) % MOD);
}

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n+1);
        for(int i = 0; i <= n; i++) parent[i] = i;
    }
    int find(int x) {
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x != y) parent[y] = x;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
//----------------------------------------
//MONOTINQUE STACK
/*
vector<int> nextSmaller(vector<int>& arr) {
    int n = arr.size();

    vector<int> nextS(n, n);

    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[i] < arr[st.top()]) {


            nextS[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return nextS;
}

vector<int> prevSmaller(vector<int>& arr) {
    int n = arr.size();

    vector<int> prevS(n, -1);

    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[i] < arr[st.top()]) {


            st.pop();
        }
        if (!st.empty()) {
            prevS[i] = st.top();
        }
        st.push(i);
    }
    return prevS;
}


int getMaxArea(vector<int>& arr) {
    vector<int> prevS = prevSmaller(arr);
    vector<int> nextS = nextSmaller(arr);

    int maxArea = 0;

    for (int i = 0; i < arr.size(); ++i) {
        int width = nextS[i] - pWUIGUYQFRrevS[i] - 1;
        int area = arr[i] * width;
        maxArea = max(maxArea, area);
    }

    return maxArea;
}
*/

struct segtree {
    vector<pair<ll,ll>> seg;
    int size;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        seg.resize(2 * size);
    }
    pair<ll,ll> merge(pair<ll,ll> x, pair<ll,ll> y) {
        if (x.F>y.F) return y;
        else if (x.F<y.F) return x;
        else return mp(x.F,x.S+y.S);
    }
    void build(vector<ll> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()){ seg[x] = {a[lx],1};}
            return;
        }
        int mid = (lx + rx) / 2;
        build(a, 2*x + 1, lx, mid);
        build(a, 2*x + 2, mid, rx);
        seg[x] = merge(seg[2*x+1],seg[2*x+2]);
    }

    void build(vector<ll> &a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            seg[x] = mp(v,1);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) set(i, v, 2*x + 1, lx, m);
        else set(i, v, 2*x + 2, m, rx);
        seg[x] = merge(seg[2*x+1],seg[2*x+2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }
    pair<ll,ll> mini(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return {LLONG_MAX, LLONG_MAX};
        if (lx >= l && rx <= r) return seg[x];
        int mid = (lx + rx) / 2;
        pair<ll,ll> s1 = mini(l, r, 2*x + 1, lx, mid);
        pair<ll,ll> s2 = mini(l, r, 2*x + 2, mid, rx);
        return merge(s1, s2);
    }

    pair<ll,ll> mini(int l, int r) {
        return mini(l, r, 0, 0, size);
    }

};
//--------------------------------------------------
//dijakstra
// vector<vector<pair<ll,ll>>> adj; // adj[u] = {v, weight}
//
// vector<ll> dijkstra(ll n, ll src) {
//     vector<ll> dist(n + 1, LLONG_MAX);
//     dist[src] = 0;
//
//     // min-heap : (dist, node)
//     priority_queue<
//         pair<ll,ll>,
//         vector<pair<ll,ll>>,
//         greater<pair<ll,ll>>
//     > pq;
//
//     pq.push({0, src});
//
//     while(!pq.empty()) {
//         auto [curr_dist, curr] = pq.top();
//         pq.pop();
//
//         if (curr_dist != dist[curr]) continue;  // skip old data
//
//         for (auto [v, w] : adj[curr]) {
//             if (dist[v] > dist[curr] + w) {
//                 dist[v] = dist[curr] + w;
//                 pq.push({dist[v], v});
//             }
//         }
//     }
//
//     return dist;
// }

struct LCA {
    // COMMENT UNUSED VECTORS TO SAVE MEMORY !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int n, LOG = 20;
    vector<vector<int>> adj;

    vector<int> depth;
    vector<vector<int>> up;

    vector<vector<long long>> upMin, upMax, upSum;
    map<pair<int,int>, long long> w;

    LCA(int n_) {
        n = n_;
        adj.assign(n+1, {});
        depth.assign(n+1, 0);
        up.assign(n+1, vector<int>(LOG+1, 0));

        upMin.assign(n+1, vector<long long>(LOG+1, LLONG_MAX));
        upMax.assign(n+1, vector<long long>(LOG+1, LLONG_MIN));
        upSum.assign(n+1, vector<long long>(LOG+1, 0));
    }

    void addEdge(int u, int v, long long weight = 0) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        w[{min(u,v), max(u,v)}] = weight;
    }
    void addEdge_modi(int u, int v, long long weight = 0) {
        adj[u].push_back(v);
       // adj[v].push_back(u);
        //w[{min(u,v), max(u,v)}] = weight;
    }

    void dfs(int v, int p) {
        up[v][0] = p;
        if (p != 0) {
            auto key = make_pair(min(v,p), max(v,p));
            long long ww = w.count(key) ? w[key] : 0;

            upMin[v][0] = ww;
            upMax[v][0] = ww;
            upSum[v][0] = ww;
        }

        for (int nxt : adj[v]) {
            if (nxt == p) continue;
            depth[nxt] = depth[v] + 1;
            dfs(nxt, v);
        }
    }

    void build(int root = 1) {
        dfs(root, 0);

        for (int j = 1; j <= LOG; j++) {
            for (int v = 1; v <= n; v++) {
                int mid = up[v][j-1];
                up[v][j] = (mid == 0 ? 0 : up[mid][j-1]);

                if (mid == 0) {
                    upMin[v][j] = upMin[v][j-1];
                    upMax[v][j] = upMax[v][j-1];
                    upSum[v][j] = upSum[v][j-1];
                } else {
                    upMin[v][j] = min(upMin[v][j-1], upMin[mid][j-1]);
                    upMax[v][j] = max(upMax[v][j-1], upMax[mid][j-1]);
                    upSum[v][j] = upSum[v][j-1] + upSum[mid][j-1];
                }
            }
        }
    }

    int lift(int a, int k) {
        for (int i = 0; i <= LOG; i++)
            if (k & (1<<i))
                a = up[a][i];
        return a;
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        a = lift(a, depth[a] - depth[b]);

        if (a == b) return a;

        for (int i = LOG; i >= 0; i--) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }
        return up[a][0];
    }

    long long jumpMin(int a, int k) {
        long long ans = LLONG_MAX;
        for (int i = 0; i <= LOG; i++)
            if (k & (1<<i)) {
                ans = min(ans, upMin[a][i]);
                a = up[a][i];
            }
        return ans;
    }
    long long jumpMax(int a, int k) {
        long long ans = LLONG_MIN;
        for (int i = 0; i <= LOG; i++)
            if (k & (1<<i)) {
                ans = max(ans, upMax[a][i]);
                a = up[a][i];
            }
        return ans;
    }
    long long jumpSum(int a, int k) {
        long long ans = 0;
        for (int i = 0; i <= LOG; i++)
            if (k & (1<<i)) {
                ans += upSum[a][i];
                a = up[a][i];
            }
        return ans;
    }

    long long queryMin(int a, int b) {
        int c = lca(a,b);
        return min(jumpMin(a, depth[a]-depth[c]),
                   jumpMin(b, depth[b]-depth[c]));
    }
    long long queryMax(int a, int b) {
        int c = lca(a,b);
        return max(jumpMax(a, depth[a]-depth[c]),
                   jumpMax(b, depth[b]-depth[c]));
    }
    long long querySum(int a, int b) {
        int c = lca(a,b);
        return jumpSum(a, depth[a]-depth[c]) +
               jumpSum(b, depth[b]-depth[c]);
    }
};




//  the number of different possible locations after exactly n steps.
// horizontal then vertical or vertical then horizontal
// void solve(int _){
//     ll n;cin>>n;
//     if (n%2==0) {
//         cout<<pow(n/2 +1,2)<<endl;
//     }
//     else {
//         cout<<2*(n/2 +1)*(n/2 +2)<<endl;
//     }
//
//
// }

// ----------------------------------
// precomputing hash for substrings
// void solve(int _) {
//     string v; cin >> v;
//     int n = v.size();
//     string mask; cin >> mask;
//     long long k; cin >> k;
//
//     vector<long long> pref(n+1), pw(n+1);
//     const long long B = 1315423911;
//     const long long M = (1LL<<61)-1;
//
//     pw[0] = 1;
//     for (int i = 0; i < n; i++) {
//         pw[i+1] = (__int128)pw[i] * B % M;
//         pref[i+1] = ((__int128)pref[i] * B + (v[i] - 'a' + 1)) % M;
//     }
//
//     auto getHash = [&](int l, int r) {
//         long long h = (pref[r] - (long long)((__int128)pref[l] * pw[r-l] % M));
//         if (h < 0) h += M;
//         return h;
//     };
//
//     unordered_set<long long> distinct;
//
//     for (int l = 0; l < n; l++) {
//         long long bad = 0;
//         for (int r = l; r < n; r++) {
//             if (mask[v[r]-'a'] == '0') bad++;
//             if (bad > k) break;
//
//             long long h = getHash(l, r+1);
//             distinct.insert(h);
//         }
//     }
//
//     cout << distinct.size() << "\n";
// }

// ------------------------------------
//  dijkastra_with_capped_numer_of_edges
// const ll INF = 1e18;
//
// struct Edge {
//     int to;
//     ll weight;
// };
//
// ll dijkastra_with_capped_numer_of_edges(int n, vector<vector<Edge>> &adj, int x, int y, int k) {
//     vector<vector<ll>> dist(n+1, vector<ll>(k+1, INF));
//     dist[x][0] = 0;
//
//     using T = tuple<ll,int,int>;
//     priority_queue<T, vector<T>, greater<T>> pq;
//     pq.push({0, x, 0});
//
//     while (!pq.empty()) {
//         auto [d, u, c] = pq.top();
//         pq.pop();
//         if (d !=dist[u][c]) continue;
//         if (u == y) return d;
//         for (auto &e : adj[u]) {
//             int v = e.to;
//             long long w = e.weight;
//
//             if (c + 1 <= k && dist[v][c+1] > d + w) {
//                 dist[v][c+1] = d + w;
//                 pq.push({dist[v][c+1], v, c+1});
//             }
//         }
//     }
//
//     long long res = INF;
//     for (int i = 0; i <= k; i++)
//         res = min(res, dist[y][i]);
//
//     return (res == INF ? -1 : res);
// }
//

int msb_pos(long long n) {
    return 63 - __builtin_clzll(n);
}

const int MAXI=1e6 +5;


void solve() {


}

int main() {
    FAST
    // seive();
    // preproc();

    ll t=1;
    // cin >> t;
    while (t--) solve();
    return 0;
}

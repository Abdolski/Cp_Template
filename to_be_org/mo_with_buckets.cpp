// Problem: D. Tree and Queries
// Contest: Codeforces - Codeforces Round 221 (Div. 1)
// URL: https://codeforces.com/problemset/problem/375/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define ll long long
#define pb push_back
#define all(x) x.begin(), x.end()
#define rep(i,a,b) for(int i=a;i<b;i++)

#pragma GCC optimize("O3,unroll-loops")

const int MAXN = 200005;

struct Query {
    int l, r, idx, k;
};

int n, q;
int block;

vector<vector<int>> adj;
vector<int> color;
vector<int> subtree_size;
vector<int> euler;

int freq[MAXN];        // freq of each color
int cntFreq[MAXN];     // how many colors have frequency = f
int bucket[MAXN];      // sqrt bucket on frequencies

int Fblock;            // block size for frequency buckets

// ---------------- DFS flatten ----------------
void dfs(int u, int p) {
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        subtree_size[u] += subtree_size[v] + 1;
        euler.pb(v);
    }
}

// ---------------- Mo comparator ----------------
bool cmp(const Query &A, const Query &B) {
    int blockA = A.l / block;
    int blockB = B.l / block;
    if (blockA != blockB) return blockA < blockB;
    return (blockA & 1) ? A.r > B.r : A.r < B.r;
}

// ---------------- Add ----------------
void add(int idx) {
    int c = color[idx];
    int oldf = freq[c];

    if (oldf > 0) {
        cntFreq[oldf]--;
        bucket[oldf / Fblock]--;
    }

    freq[c]++;
    int newf = freq[c];

    cntFreq[newf]++;
    bucket[newf / Fblock]++;
}

// ---------------- Remove ----------------
void remove_(int idx) {
    int c = color[idx];
    int oldf = freq[c];

    cntFreq[oldf]--;
    bucket[oldf / Fblock]--;

    freq[c]--;
    int newf = freq[c];

    if (newf > 0) {
        cntFreq[newf]++;
        bucket[newf / Fblock]++;
    }
}

// ---------------- Query ≥ k ----------------
int queryFreq(int k) {
    int ans = 0;

    int startBlock = k / Fblock;
    int maxF = n;

    // first partial bucket
    int end = min(maxF, (startBlock + 1) * Fblock - 1);
    for (int f = k; f <= end; f++)
        ans += cntFreq[f];

    // full buckets
    for (int b = startBlock + 1; b <= maxF / Fblock; b++)
        ans += bucket[b];

    return ans;
}

// ---------------- Solve ----------------
void solve() {
    cin >> n >> q;

    adj.assign(n+1, {});
    color.assign(n+1, 0);
    subtree_size.assign(n+1, 0);
    euler.clear();

    memset(freq, 0, sizeof(freq));
    memset(cntFreq, 0, sizeof(cntFreq));
    memset(bucket, 0, sizeof(bucket));

    rep(i,1,n+1) cin >> color[i];

    rep(i,0,n-1) {
        int u,v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(1,0);
    euler.pb(1);
    reverse(all(euler));

    vector<int> pos(n+1);
    rep(i,0,n)
        pos[euler[i]] = i;

    vector<Query> queries(q);
    rep(i,0,q) {
        int x,k;
        cin >> x >> k;
        queries[i] = { pos[x], pos[x] + subtree_size[x], i, k };
    }

    block = sqrt(n);
    Fblock = sqrt(n);   // frequency bucket size

    sort(all(queries), cmp);

    vector<int> ans(q);

    int L = 0, R = -1;

    for (auto &qr : queries) {
        while (L > qr.l) add(euler[--L]);
        while (R < qr.r) add(euler[++R]);
        while (L < qr.l) remove_(euler[L++]);
        while (R > qr.r) remove_(euler[R--]);

        ans[qr.idx] = queryFreq(qr.k);
    }

    rep(i,0,q)
        cout << ans[i] << endl;
}

signed main() {
    FAST;
    solve();
}
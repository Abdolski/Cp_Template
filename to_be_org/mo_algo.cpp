#include <bits/stdc++.h>
using namespace std;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

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
#define rep(i,x,n) for(int i = x; i < n; i++)
#define per(i,x,n) for(int i = x; i >=n; i--)
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using pll = pair<ll, ll>;
const ll INF = 1e18;
const ll inf = -1e18;
const ll mod = 1e9 + 7;
const ll MOD = 998244353;
const ll dcinq = 1e5 + 5;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }
// #define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
// #define r_ordered_set tree<ll, null_type,greater<ll>, rb_tree_tag,tree_order_statistics_node_update>

int dx[4] = {-1, 1, -1, 1};
int dy[4] = {-1, -1, 1, 1};


const int MAXN = 200000;
vector<int> a;
vector<int> b;
vector<int> values;
int freq[1000005]; 
int distinctCnt = 0;

struct Query {
    int l, r, idx;
};

int block;

bool cmp(Query &A, Query &B) {
    int blockA = A.l / block;
    int blockB = B.l / block;
    if (blockA != blockB) return blockA < blockB;
    return (blockA & 1) ? A.r > B.r : A.r < B.r; 
}

void add(int x) {
    if (freq[x] == 0) distinctCnt++;
    freq[x]++;
}

void remove_(int x) {
    freq[x]--;
    if (freq[x] == 0) distinctCnt--;
}

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    a.resize(n);
    b.resize(n);
    
    values.resize(n);

    
    for (int i = 0; i < n; i++) cin >> a[i];
    // vector<int> b = values;
	// sort(b.begin(), b.end());
	// b.erase(unique(b.begin(), b.end()), b.end());
// 	
	// for (int i = 0; i < n; i++) {
	    // a[i] = lower_bound(b.begin(), b.end(), values[i]) - b.begin();
	// }

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; 
        queries[i].r--;
        queries[i].idx = i;
    }

    block = sqrt(n);

    sort(queries.begin(), queries.end(), cmp);

    vector<int> ans(q);

    int L = 0, R = -1;

    for (auto &qr : queries) {
        int l = qr.l, r = qr.r;

        while (L > l) add(a[--L]);
        while (R < r) add(a[++R]);
        while (L < l) remove_(a[L++]);
        while (R > r) remove_(a[R--]);

        ans[qr.idx] = distinctCnt;
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << "\n";
}

void solve(){
	
}



signed main() {
    FAST;
    auto begin = std::chrono::high_resolution_clock::now();
// #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
// #endif
    ll t = 1;
    //cin >> t;
    while (t--) solve();
#ifndef ONLINE_JUDGE
    auto end = std::chrono::high_resolution_clock::now();
    cout << setprecision(4) << fixed;
    cout << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count()
         << " seconds" << endl;
#endif
}
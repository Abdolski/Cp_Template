#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

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

using pll = pair<ll, ll>;
const ll INF = 1e18;
const ll inf = -1e18;
const ll mod = 1e9 + 7;
const ll MOD = 998244353;
const ll dcinq = 1e5 + 5;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }
#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

const int MAXI = 1e5 + 5;

vector<vi > adj;


const int MAXN = 100000;
vector<int> g[MAXN + 1];
ll dp[MAXN + 1][2];

void dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = 1;

    for (int v : g[u]) {
        if (v == parent) continue;
        dfs(v, u);

        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
}

int msb_pos(long long n) {
    return 63 - __builtin_clzll(n);
}

void solve() {

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]) << "\n";

}



int main() {
    FAST
    // seive();
    // preproc();
    ll t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}

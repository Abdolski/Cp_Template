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



template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0;
    ll n; vector<T> seg;
    
    T comb(T a, T b) { return a+b; }
    
    void init(ll _n) { n = _n; seg.assign(2*n,ID); }
    
    void pull(ll p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    
    void upd(ll p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    
    T query(ll l, ll r) {   // sum on llerval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }return comb(ra,rb);
    }
};
const int N = 2e5 + 5;
const int LG = 20;
vector<ll> adj[N];
int childs[N], par[N], bg[N], tin[N], tout[N], val[N], dep[N];
int up[N][LG];
Seg<ll> s;
int timer = 0;
 
void dfs_init(int v = 1, int p = 0) {
    dep[v] = dep[p] + 1;
    up[v][0] = p;
    for (int l = 1; l < LG; l++) {
        up[v][l] = up[up[v][l - 1]][l - 1];
    }
    bg[v] = 0;
    for (auto child: adj[v]) {
        if (child == p)continue;
        dfs_init(child, v);
        if (childs[child] > childs[bg[v]]) {
            bg[v] = child;
        }
        childs[v] += childs[child];
    }
    childs[v]++;
}
 
void update(int v, ll newVal) {
    val[v] = newVal;
    s.upd(tin[v], newVal);   
}
 
 
void dfs(int v = 1, int p = 0, int top = 1) {
    tin[v] = ++timer;
    s.upd(timer, val[v]);
    par[v] = top;
    if (bg[v])dfs(bg[v], v, top);
    for (auto child: adj[v]) {
        if (child == bg[v] || child == p) continue;
        dfs(child, v, child);
    }
    tout[v] = timer;
}
 
void init() {
    s.init(N);
    dep[0] = 0;
    dfs_init();
    dfs();
}
 
int lca(int u, int v) {
    if (dep[u] < dep[v])swap(u, v);
    int k = dep[u] - dep[v];
    for (int l = 0; l < LG; l++) {
        if (k & (1 << l))u = up[u][l];
    }
    if (u == v) return u;
    for (int l = LG - 1; l >= 0; l--) {
        if (up[v][l] != up[u][l])u = up[u][l], v = up[v][l];
    }
    return up[v][0];
}
 
int merge(int a,int b){
	return a+b;
}
// u should be the ancesstor of v
int path(int v, int u) {
    ll ans = 0;
    while (v != u) {
        if (dep[par[v]] <= dep[u]) {
            ans = merge(ans, s.query(tin[u] + 1, tin[v]));
            v = u;
        } else {
            ans = merge(ans, s.query(tin[par[v]], tin[v]));
            v = up[par[v]][0];
        }
    }
    return ans;
}
 
int query(int v, int u) {
    ll l = lca(u, v);
    ll ans = path(v, l);
    ans = merge(ans, path(u, l));
    ans = merge(val[l], ans);
    return ans;
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
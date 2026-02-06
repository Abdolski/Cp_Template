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


struct StringHash {
    static const long long mod = 1000000007;
    static const long long base = 91138233;

    vector<long long> h, p;

    StringHash(string &s) {
        int n = s.size();
        h.resize(n+1);
        p.resize(n+1);
        p[0] = 1;
        for(int i=0;i<n;i++){
            h[i+1] = (h[i] * base + (s[i] - 'a' + 1)) % mod;
            p[i+1] = (p[i] * base) % mod;
        }
    }

    long long get(int l, int r) {
        return (h[r] - h[l]*p[r-l] % mod + mod) % mod;
    }
};

struct DH {
    const long long mod1 = 1000000007;
    const long long mod2 = 1000000009;
    const long long base = 91138233;

    vector<long long> h1,h2,p1,p2;

    DH(string &s){
        int n=s.size();
        h1.resize(n+1); h2.resize(n+1);
        p1.resize(n+1); p2.resize(n+1);
        p1[0]=p2[0]=1;

        for(int i=0;i<n;i++){
            h1[i+1]=(h1[i]*base + s[i])%mod1;
            h2[i+1]=(h2[i]*base + s[i])%mod2;
            p1[i+1]=(p1[i]*base)%mod1;
            p2[i+1]=(p2[i]*base)%mod2;
        }
    }

    pair<long long,long long> get(int l,int r){
        long long x1=(h1[r]-h1[l]*p1[r-l]%mod1+mod1)%mod1;
        long long x2=(h2[r]-h2[l]*p2[r-l]%mod2+mod2)%mod2;
        return {x1,x2};
    }
};

struct FastHash {
    static const uint64_t base = 1315423911;
    vector<uint64_t> h,p;

    FastHash(string &s){
        int n=s.size();
        h.resize(n+1);
        p.resize(n+1);
        p[0]=1;
        for(int i=0;i<n;i++){
            h[i+1]=h[i]*base + s[i];
            p[i+1]=p[i]*base;
        }
    }

    uint64_t get(int l,int r){
        return h[r] - h[l]*p[r-l];
    }
};


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
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
const ll INF = 1e18;
const ll inf = -1e18;
const ll mod = 1e9 + 7;
const ll MOD = 998244353;
const ll dcinq=1e5+5;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }


ll add(ll x, ll y) {
    x += y;
    if (x >= mod) x -= mod;
    return x;
}

ll mul(ll x, ll y) {
    return (x * y) % mod;
}



void solve() {
    ll n;cin>>n;
    vi a(n);
    const int INF = 1e9;
    f(i,0,n) cin>>a[i];

    vector<int> d(n+1, INF);
    d[0] = -INF;

    for (int i = 0; i < n; i++) {
        int l = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[l-1] < a[i] && a[i] < d[l])
            d[l] = a[i];
    }

    int ans = 0;
    for (int l = 0; l <= n; l++) {
        if (d[l] < INF)
            ans = l;
    }
    cout << ans << endl;



}



int main() {
    FAST
   //  seive();
   // preproc();



    ll t=1;

    // cin >> t;
    while(t--) {
        solve();


    }
    return 0;
}
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

struct segtree {
    struct Node {
        ll mn, mx, sum;
    };

    int size;
    vector<Node> seg;

    void init(int n) {
        size = 1;
        while (size < n) size <<= 1;
        seg.assign(2 * size, {LLONG_MAX, LLONG_MIN, 0});
    }

    Node merge(Node a, Node b) {
        return {
            min(a.mn, b.mn),
            max(a.mx, b.mx),
            a.sum + b.sum
        };
    }

    void build(vector<ll> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size())
                seg[x] = {a[lx], a[lx], a[lx]};
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2*x+1, lx, m);
        build(a, 2*x+2, m, rx);
        seg[x] = merge(seg[2*x+1], seg[2*x+2]);
    }

    void build(vector<ll> &a) {
        build(a, 0, 0, size);
    }

    void set_min(int i, ll v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            seg[x].mn = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) set_min(i, v, 2*x+1, lx, m);
        else set_min(i, v, 2*x+2, m, rx);
        seg[x].mn = min(seg[2*x+1].mn, seg[2*x+2].mn);
    }

    void set_max(int i, ll v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            seg[x].mx = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) set_max(i, v, 2*x+1, lx, m);
        else set_max(i, v, 2*x+2, m, rx);
        seg[x].mx = max(seg[2*x+1].mx, seg[2*x+2].mx);
    }

    void set_sum(int i, ll v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            seg[x].sum = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) set_sum(i, v, 2*x+1, lx, m);
        else set_sum(i, v, 2*x+2, m, rx);
        seg[x].sum = seg[2*x+1].sum + seg[2*x+2].sum;
    }

    void set_min(int i, ll v) { set_min(i, v, 0, 0, size); }
    void set_max(int i, ll v) { set_max(i, v, 0, 0, size); }
    void set_sum(int i, ll v) { set_sum(i, v, 0, 0, size); }

    ll query_min(int l, int r, int x, int lx, int rx) {
        if (rx <= l || lx >= r) return LLONG_MAX;
        if (lx >= l && rx <= r) return seg[x].mn;
        int m = (lx + rx) / 2;
        return min(
            query_min(l, r, 2*x+1, lx, m),
            query_min(l, r, 2*x+2, m, rx)
        );
    }

    ll query_max(int l, int r, int x, int lx, int rx) {
        if (rx <= l || lx >= r) return LLONG_MIN;
        if (lx >= l && rx <= r) return seg[x].mx;
        int m = (lx + rx) / 2;
        return max(
            query_max(l, r, 2*x+1, lx, m),
            query_max(l, r, 2*x+2, m, rx)
        );
    }

    ll query_sum(int l, int r, int x, int lx, int rx) {
        if (rx <= l || lx >= r) return 0;
        if (lx >= l && rx <= r) return seg[x].sum;
        int m = (lx + rx) / 2;
        return
            query_sum(l, r, 2*x+1, lx, m) +
            query_sum(l, r, 2*x+2, m, rx);
    }

    ll query_min(int l, int r) { return query_min(l, r, 0, 0, size); }
    ll query_max(int l, int r) { return query_max(l, r, 0, 0, size); }
    ll query_sum(int l, int r) { return query_sum(l, r, 0, 0, size); }


};

void solve() {
    int n;cin>>n;
    vi a(n);
    vl h(n);

    f(i,0,n) cin>>h[i];
    f(i,0,n) {
        cin>>a[i];
    }
    segtree t;
    t.init(n + 1);

    const ll NEG_INF = -1e18;

    for (int i = 0; i <= n; i++) {
        t.set_max(i, NEG_INF);
    }
    t.set_max(0, 0);

    for (int i = 0; i < n; i++) {
        ll best = t.query_max(0, h[i]);
        ll cur = best + a[i];
        ll old = t.query_max(h[i], h[i] + 1);
        t.set_max(h[i], max(old, cur));
    }

    ll ans = t.query_max(0, n + 1);
    cout << ans << "\n";




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

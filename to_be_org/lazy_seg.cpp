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

int dx[4] = {-1, 1, 0,0};
int dy[4] = {0,0, 1, -1};

vl Divisors(long long n) {
    vector<long long> divisors;

    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i)
                divisors.push_back(n / i);
        }
    }

    sort(divisors.begin(), divisors.end());

    return  divisors;
}

template <typename T>
struct SegTree {
    enum Type { MIN, MAX, SUM, XOR, GCD };

    int n;
    vector<T> tree, lazy;
    Type type;
    T neutral;

    SegTree(int n, Type type) : n(n), type(type) {
        neutral = neutral_element();
        tree.assign(4 * n, neutral);
        lazy.assign(4 * n, 0);
    }

    T neutral_element() {
        if (type == MIN) return numeric_limits<T>::max();
        if (type == MAX) return numeric_limits<T>::min();
        if (type == SUM) return T(0);
        if (type == XOR) return T(0);
        if (type == GCD) return T(0);
        return T(0);
    }

    T merge(T a, T b) {
        if (type == MIN) return min(a, b);
        if (type == MAX) return max(a, b);
        if (type == SUM) return a + b;
        if (type == XOR) return a ^ b;
        if (type == GCD) return gcd(a, b);
        return a;
    }

    void apply(int node, int l, int r, T val) {
        if (type == SUM) tree[node] += val * (r - l + 1);
        else if (type == MIN || type == MAX) tree[node] += val;
        else if (type == XOR) {
            if ((r - l + 1) % 2) tree[node] ^= val;
        }
        lazy[node] += val;
    }

    void push(int node, int l, int r) {
        if (lazy[node] == 0 || l == r) return;
        int mid = (l + r) / 2;
        apply(node * 2, l, mid, lazy[node]);
        apply(node * 2 + 1, mid + 1, r, lazy[node]);
        lazy[node] = 0;
    }

    void build(const vector<T>& a, int node, int l, int r) {
        if (l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, node * 2, l, mid);
        build(a, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void build(const vector<T>& a) {
        build(a, 1, 0, n - 1);
    }

    // range add
    void update(int node, int l, int r, int ql, int qr, T val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int l, int r, T val) {
        update(1, 0, n - 1, l, r, val);
    }

    T query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return neutral;
        if (ql <= l && r <= qr) return tree[node];
        push(node, l, r);
        int mid = (l + r) / 2;
        return merge(
            query(node * 2, l, mid, ql, qr),
            query(node * 2 + 1, mid + 1, r, ql, qr)
        );
    }

    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};


SegTree<int> st_min(n, SegTree<int>::MIN);


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
    cin >> t;
    while (t--) solve();
#ifndef ONLINE_JUDGE
    auto end = std::chrono::high_resolution_clock::now();
    cout << setprecision(4) << fixed;
    cout << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count()
         << " seconds" << endl;
#endif
}
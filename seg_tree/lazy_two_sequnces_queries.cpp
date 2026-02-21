#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

struct Node {
    ll sumA = 0;
    ll sumB = 0;
    ll sumAB = 0;
    ll lazyA = 0;
    ll lazyB = 0;
};

const int MAXN = 200000 + 5;
Node st[4 * MAXN];
ll A[MAXN], B[MAXN];

inline ll mod(ll x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

void pull(int v) {
    st[v].sumA  = mod(st[v*2].sumA  + st[v*2+1].sumA);
    st[v].sumB  = mod(st[v*2].sumB  + st[v*2+1].sumB);
    st[v].sumAB = mod(st[v*2].sumAB + st[v*2+1].sumAB);
}

void apply(int v, int l, int r, ll addA, ll addB) {
    int len = r - l + 1;

    st[v].sumAB = mod(st[v].sumAB
        + addA * st[v].sumB
        + addB * st[v].sumA
        + addA * addB % MOD * len);

    st[v].sumA = mod(st[v].sumA + addA * len);
    st[v].sumB = mod(st[v].sumB + addB * len);

    st[v].lazyA = mod(st[v].lazyA + addA);
    st[v].lazyB = mod(st[v].lazyB + addB);
}

void push(int v, int l, int r) {
    if (st[v].lazyA == 0 && st[v].lazyB == 0) return;
    int m = (l + r) >> 1;
    apply(v*2,   l,   m, st[v].lazyA, st[v].lazyB);
    apply(v*2+1, m+1, r, st[v].lazyA, st[v].lazyB);
    st[v].lazyA = st[v].lazyB = 0;
}

void build(int v, int l, int r) {
    if (l == r) {
        st[v].sumA = mod(A[l]);
        st[v].sumB = mod(B[l]);
        st[v].sumAB = mod(A[l] * B[l]);
        return;
    }
    int m = (l + r) >> 1;
    build(v*2, l, m);
    build(v*2+1, m+1, r);
    pull(v);
}

void update(int v, int l, int r, int ql, int qr, ll addA, ll addB) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        apply(v, l, r, mod(addA), mod(addB));
        return;
    }
    push(v, l, r);
    int m = (l + r) >> 1;
    update(v*2, l, m, ql, qr, addA, addB);
    update(v*2+1, m+1, r, ql, qr, addA, addB);
    pull(v);
}

ll query(int v, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return st[v].sumAB;
    push(v, l, r);
    int m = (l + r) >> 1;
    return mod(query(v*2, l, m, ql, qr)
             + query(v*2+1, m+1, r, ql, qr));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) cin >> B[i];

    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r; ll x;
            cin >> l >> r >> x;
            update(1, 1, n, l, r, x, 0);
        }
        else if (type == 2) {
            int l, r; ll x;
            cin >> l >> r >> x;
            update(1, 1, n, l, r, 0, x);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << "\n";
        }
    }
}

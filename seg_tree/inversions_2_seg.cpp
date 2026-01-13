
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
#define vi vector<ll>
#define vl vector<int>
#define mp(x, y) make_pair(x, y)
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
#define all(x) x.begin(), x.end()
#define rep(i,x,n) for(int i = x; i < n; i++)
#define per(i,x,n) for(int i = x; i >=n; i--)
#define tr(a,i) for(auto i = a.begin(); i != a.end(); i++)
using pll = pair<ll, ll>;
const ll INF = 1e18;
const ll inf = -1e18;
const ll mod = 1e9 + 7;
const ll MOD = 998244353;
const ll dcinq=1e5+5;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }
#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

struct segtree {
    vl tree;
    int size;
    void init (int n) {
        size=1;
        while (size < n) size *= 2;
        tree.resize(2*size,0);

    }
    void build(vl &a,ll s,ll e,ll node) {
        if (s==e) {
            tree[node]=a[s];
            return;
        }
        ll mid=(s+e)/2;
        build(a,s,mid,2*node+1);
        build(a,mid+1,e,2*node+2);
        tree[node]=tree[node*2+1]+tree[node*2+2];
        return;
    }
    void update(ll s,ll e,ll node,ll index,ll value) {
        if (index < s || index > e) {
            return;
        }
        if (s==e) {
            tree[node]=value;
            return;
        }
        ll mid=(s+e)/2;
        update(s,mid,2*node+1,index,value);
        update(mid+1,e,2*node+2,index,value);
        tree[node]=tree[node*2+1]+tree[node*2+2];
    }
    int query(ll s,ll e,ll node,ll index) {
        if (s==e) {
            return s;
        }
        if (index>tree[2*node+1]) {
            index=index-tree[2*node+1];
            ll mid=(s+e)/2;
            return query(mid+1,e,2*node+2,index);

        }
        else {
            ll mid=(s+e)/2;
            return query(s,mid,2*node+1,index);
        }
    }
    void coo() {
        for (int i = 0; i <tree.size(); i++) {
            cout<<tree[i]<<" ";
        }
        cout<<endl;

    }

};
void solve() {
    ll n;cin>>n;
    vl a(n);
    segtree st;
    st.init(n);
    for (int i = 0; i < n; i++) {
        cin>>a[i];
    }
    for (int i = 0; i < n; i++) {
        st.update(0,n-1,0,i,1);
    }
    vector<int> anss;
    for (int i = n-1; i >=0; i--) {
        int ans = st.query(0,n-1,0,(i+1)-a[i]);
        anss.pb(ans+1);
        st.update(0,n-1,0,ans,0);

    }
    reverse(anss.begin(),anss.end());
    for (auto x:anss) {
        cout << x << " ";
    }
    cout << endl;
}


int main() {
    FAST
    // seive();
    // preproc();
    ll t=1;
    cin >> t;
    while(t--) solve();
    return 0;
}

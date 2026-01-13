//
// Created by expert on 1/11/2026.
//
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<long long>> dist(n, vector<long long>(n, INF));
    vector<int> deg(n, 0);
    long long sumEdges = 0;

    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--; v--;

        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);

        deg[u]++;
        deg[v]++;
        sumEdges += w;
    }

    // Floyd–Warshall
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // Collect odd-degree vertices
    vector<int> odd;
    for (int i = 0; i < n; i++)
        if (deg[i] % 2 == 1)
            odd.push_back(i);

    int k = odd.size();

    // If already Eulerian
    if (k == 0) {
        cout << sumEdges << "\n";
        return 0;
    }

    // DP over subsets
    int FULL = 1 << k;
    vector<long long> dp(FULL, INF);
    dp[0] = 0;

    for (int mask = 0; mask < FULL; mask++) {
        int cnt = __builtin_popcount(mask);
        if (cnt % 2) continue;

        int first = -1;
        for (int i = 0; i < k; i++) {
            if (!(mask & (1 << i))) {
                first = i;
                break;
            }
        }

        if (first == -1) continue;

        for (int j = first + 1; j < k; j++) {
            if (!(mask & (1 << j))) {
                int newMask = mask | (1 << first) | (1 << j);
                dp[newMask] = min(
                    dp[newMask],
                    dp[mask] + dist[odd[first]][odd[j]]
                );
            }
        }
    }

    cout << sumEdges + dp[FULL - 1] << "\n";
    return 0;
}

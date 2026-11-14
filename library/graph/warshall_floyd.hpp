#pragma once

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Warshall-Floyd (all pairs shortest paths)
 *
 * d is the distance matrix; initialize unreachable pairs with INF
 * (default: numeric_limits<T>::max() / 4) and d[i][i] = 0.
 * The matrix is updated in place.
 *
 * @returns false if a negative cycle exists (d[i][i] < 0), true otherwise.
 *
 * @complexity O(n^3)
 */
template <class T>
bool warshall_floyd(vector<vector<T>>& d, T INF = numeric_limits<T>::max() / 4) {
    int n = (int)d.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (d[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (d[k][j] == INF) continue;
                T nd = d[i][k] + d[k][j];
                if (nd < d[i][j]) d[i][j] = nd;
            }
        }
    }

    for (int i = 0; i < n; i++)
        if (d[i][i] < 0) return false;
    return true;
}

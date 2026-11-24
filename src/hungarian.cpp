#include "hungarian.hpp"

#include <tuple>
#include <numeric>
#include <vector>

namespace {

std::tuple<std::vector<double>, std::vector<double>, std::vector<int>, std::vector<int>> initialize(const std::vector<std::vector<double>>& cost) {
    const int N = static_cast<int>(cost.size());

    std::vector<double> u = std::vector<double>(N);
    std::vector<double> v = std::vector<double>(N);
    std::vector<int> p = std::vector<int>(N);
    std::vector<int> q = std::vector<int>(N);

    for (int i = 0; i < N; i++) {
        u[i] = cost[i][0];

        for (int j = 1; j < N; j++) {
            if (u[i] > cost[i][j]) {
                u[i] = cost[i][j];
            }
        }

        v[i] = 0;
        p[i] = -1;
        q[i] = -1;
    }

    return {u, v, p, q};
}

std::tuple<std::vector<double>, std::vector<double>, std::vector<int>, int> search(
    const std::vector<std::vector<double>>& cost,
    std::vector<double>& u,
    std::vector<double>& v,
    std::vector<int>& q,
    int k
) {
    const int N = static_cast<int>(cost.size());

    std::vector<bool> I = std::vector<bool>(N, false);
    std::vector<bool> J = std::vector<bool>(N, false);
    std::vector<int> pi = std::vector<int>(N);
    std::vector<double> delta = std::vector<double>(N);
    int j;
    double _delta;

    I[k] = true;

    for (j = 0; j < N; j++) {
        delta[j] = cost[k][j] - u[k] - v[j];
        pi[j] = k;
    }

    for (int tau = 0; tau < N; tau++) {
        j = -1;

        for (int _j = 0; _j < N; _j++) {
            if (!J[_j] && (j == -1 || delta[_j] < delta[j])) {
                j = _j;
            }
        }

        _delta = delta[j];

        for (int i = 0; i< N; i++) {
            if (I[i]) {
                u[i] += _delta;
            }

            if (J[i]) {
                v[i] -= _delta;
            } else {
                delta[i] -= _delta;
            }
        }

        if (q[j] == -1) {
            break;
        }

        const int i = q[j];
        I[i] = true;
        J[j] = true;

        for (int _j = 0; _j < N; _j++) {
            if (J[_j]) {
                continue;
            }

            double r_ij = cost[i][_j] - u[i] - v[_j];

            if (delta[_j] > r_ij) {
                delta[_j] = r_ij;
                pi[_j] = i;
            }
        }
    }

    return {u, v, pi, j};
}

std::tuple<std::vector<int>, std::vector<int>> traverse(std::vector<int>& p, std::vector<int>& q, std::vector<int>& pi, int k, int j) {
    const int N = static_cast<int>(p.size());

    int i, _j;

    for (int tau = 0; tau < N; tau++) {
        i = pi[j];
        _j = p[i];
        p[i] = j;
        q[j] = i;

        if (i == k) {
            break;
        }

        j = _j;
    }

    return {p, q};
}
}

std::vector<int> hungarian(
    const std::vector<std::vector<double>>& cost
) {
    const int N = static_cast<int>(cost.size());

    auto [u, v, p, q] = initialize(cost);

    std::vector<int> pi;
    int j;

    for (int k = 0; k < N; k++) {
        std::tie(u, v, pi, j) = search(cost, u, v, q, k);
        std::tie(p, q) = traverse(p, q, pi, k, j);
    }

    return p;
}

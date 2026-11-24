#include "hungarian.hpp"

#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

volatile std::size_t sink = 0;

int main() {
    const int N = 30;
    const int T = 1000;  // trials

    std::mt19937 gen(0);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::vector<std::vector<double>> cost(N, std::vector<double>(N));

    std::chrono::steady_clock::duration elapsed_time{};

    for (int t = 0; t < T; ++t) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cost[i][j] = dist(gen);
            }
        }

        const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        const std::vector<int> assignment = hungarian(cost);
        const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        elapsed_time += end - start;
        sink += static_cast<std::size_t>(assignment[0]);
    }

    const double average_us = std::chrono::duration<double, std::micro>(elapsed_time).count() / T;

    std::cout << "Matrix size: " << N << " x " << N << '\n'
            << "Trials: " << T << '\n'
            << std::fixed << std::setprecision(3)
            << "hungarian: " << average_us << " us/call\n";
}

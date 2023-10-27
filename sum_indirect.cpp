#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>  // Include this header for lrand48()

void setup(int64_t N, uint64_t A[]) {
    // Initialize A with random values for the indirect sum implementation
    for (int64_t i = 0; i < N; ++i) {
        A[i] = lrand48() % N; // Initialize A with random values
    }
}

int64_t sum(int64_t N, uint64_t A[]) {
    int64_t result = 0;

    // Insert timer instrumentation here
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int64_t i = 0; i < N; ++i) {
        result += A[i]; // Perform the sum operation for the indirect sum implementation
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Elapsed time for indirect sum is: " << elapsed.count() << " seconds" << std::endl;

    // Calculate bytes, accesses, capacity, memory bandwidth utilization, and average memory latency
    double bytes = N * sizeof(uint64_t);
    double accesses = N;
    double capacity = 204.8; // Theoretical peak memory bandwidth in GB/s

    // Calculate memory bandwidth utilization (in GB/s)
    double memory_bandwidth_utilized = (bytes / (elapsed.count() * 1e9)) / capacity * 100.0;

    // Calculate average memory latency (in nanoseconds)
    double avg_memory_latency = (elapsed.count() * 1e9) / accesses;

    std::cout << "Memory bandwidth utilization: " << memory_bandwidth_utilized << "%" << std::endl;
    std::cout << "Average memory latency: " << avg_memory_latency << " nanoseconds" << std::endl;

    return result;
}

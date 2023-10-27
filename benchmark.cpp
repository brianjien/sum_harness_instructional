//
// (C) 2022-2023, E. Wes Bethel
// benchmark-* harness for running different versions of the sum study
//    over different problem sizes
//
// usage: no command line arguments
// set problem sizes, block sizes in the code below
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <string.h>


extern void setup(int64_t n, uint64_t A[]);
extern int64_t sum(int64_t n, uint64_t A[]);

/* The benchmarking program */
int main(int argc, char** argv) 
{
   std::cout << std::fixed << std::setprecision(4);

#define MAX_PROBLEM_SIZE 1 << 28  //  256M
   std::vector<int64_t> problem_sizes{ MAX_PROBLEM_SIZE >> 5, MAX_PROBLEM_SIZE >> 4, MAX_PROBLEM_SIZE >> 3, MAX_PROBLEM_SIZE >> 2, MAX_PROBLEM_SIZE >> 1, MAX_PROBLEM_SIZE};
   
   std::vector<uint64_t> A(MAX_PROBLEM_SIZE);

   int64_t t;
   int n_problems = problem_sizes.size();

   /* For each test size */
   for (int64_t n : problem_sizes) 
   {
      printf("Working on problem size n=%lld \n", n);

      // invoke user code to set up the problem
      setup(n, &A[0]);

      // insert your timer code here
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

      // invoke method to perform the sum
      t = sum(n, &A[0]);

      // insert your end timer code here, and print out elapsed time for this problem size
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << " Elapsed time is : " << elapsed.count() << " " << std::endl;
      printf(" Sum result = %lld \n",t);
    // Calculate bytes, accesses, capacity, memory bandwidth utilization, and average memory latency
    double bytes = n * sizeof(uint64_t);
    double accesses = n;
    double capacity = 204.8; // Theoretical peak memory bandwidth in GB/s

    // Calculate memory bandwidth utilization (in GB/s)
    double memory_bandwidth_utilized = (bytes / (elapsed.count() * 1e9)) / capacity * 100.0;

    // Calculate average memory latency (in nanoseconds)
    double avg_memory_latency = (elapsed.count() * 1e9) / accesses;

      double mflops = ((n/1000000) / elapsed.count()) ;
    std::cout << "Memory bandwidth utilization: " << memory_bandwidth_utilized << "%" << std::endl;
    std::cout << "Average memory latency: " << avg_memory_latency << " nanoseconds" << std::endl;
          std::cout << "MFLOP/s: " << mflops << std::endl;

   } // end loop over problem sizes
}

// EOF

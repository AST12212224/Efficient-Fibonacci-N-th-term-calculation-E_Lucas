#include <stdio.h>
#include <time.h>
#include <stdint.h>

// Function to calculate Fibonacci using a loop (No Recursion)
long long fibonacci_iterative(int n) {
    if (n == 1) return 0;  // Base case: Fib(1) = 0
    if (n == 2 || n == 3) return 1;  // Base case: Fib(2) & Fib(3) = 1

    long long prev1 = 1, prev2 = 1, fib = 1;
    for (int i = 4; i <= n; i++) {  // Start from 4 because Fib(1,2,3) are pre-defined
        fib = prev1 + prev2;
        prev1 = prev2;
        prev2 = fib;
    }
    return fib;
}

int main() {
    int n;
    printf("Enter the position in Fibonacci sequence: ");
    scanf("%d", &n);

    // Open the CSV file for writing
    FILE *file = fopen("fibonacci_iterative_results.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write the CSV header
    fprintf(file, "Index,Fibonacci Number,Execution Time (seconds),Execution Time (nanoseconds)\n");

    for (int i = 1; i <= n; i++) {
        // High-precision timing
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);  // Start time

        long long result = fibonacci_iterative(i);

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);  // End time

        // Calculate elapsed time in nanoseconds
        uint64_t time_ns = (uint64_t)(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        double time_sec = (double)time_ns / 1e9; // Convert to seconds

        // Write data to CSV file with ultra-precise time
        fprintf(file, "%d,%lld,%.12f,%llu\n", i, result, time_sec, time_ns);

        // Print to console
        printf("Fibonacci(%d) = %lld, Time taken: %.12f seconds (%llu ns)\n", i, result, time_sec, time_ns);
    }

    // Close the file
    fclose(file);
    printf("Results saved to fibonacci_iterative_results.csv\n");

    return 0;
}

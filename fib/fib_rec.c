#include <stdio.h>
#include <time.h>
#include <stdint.h>

// Recursive function to calculate Fibonacci numbers
long double fibonacci(int n) {
    if (n == 1)
        return 0.0; // f(1) = 0
    if (n == 2)
        return 1.0; // f(2) = 1
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    printf("Enter the position in Fibonacci sequence: ");
    scanf("%d", &n);

    // Open the CSV file for writing
    FILE *file = fopen("fibonacci_results.csv", "w");
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

        long double result = fibonacci(i);

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);  // End time

        // Calculate elapsed time
        uint64_t time_ns = (uint64_t)(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        double time_sec = (double)time_ns / 1e9; // Convert to seconds

        // Write data to CSV file with ultra-precise time
        fprintf(file, "%d,%Lf,%.12f,%llu\n", i, result, time_sec, time_ns);

        // Print to console
        printf("Fibonacci(%d) = %Lf, Time taken: %.12f seconds (%llu ns)\n", i, result, time_sec, time_ns);
    }

    // Close the file
    fclose(file);
    printf("Results saved to fibonacci_results.csv\n");

    return 0;
}

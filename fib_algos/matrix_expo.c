#include <stdio.h>
#include <time.h>
#include <stdint.h>

// Function to multiply two 2x2 matrices
void multiply(long long F[2][2], long long M[2][2]) {
    long long x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    long long y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    long long z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    long long w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

// Function to raise a matrix to power n using binary exponentiation
void power(long long F[2][2], long long n) {
    if (n == 0 || n == 1)
        return;

    long long M[2][2] = {{1, 1}, {1, 0}};

    power(F, n / 2);
    multiply(F, F);

    if (n % 2 != 0)
        multiply(F, M);
}

// Function to compute Fibonacci using Matrix Exponentiation
long long fibonacci_matrix(long long n) {
    if (n == 0)
        return 0;
    
    long long F[2][2] = {{1, 1}, {1, 0}};
    power(F, n - 1);

    return F[0][0];  // F(n)
}

int main() {
    int n;
    printf("Enter the position in Fibonacci sequence: ");
    scanf("%d", &n);

    // Open CSV file for writing
    FILE *file = fopen("fibonacci_matrix_results.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write CSV header
    fprintf(file, "Index,Fibonacci Number,Execution Time (seconds),Execution Time (nanoseconds)\n");

    for (int i = 1; i <= n; i++) {
        // High-precision timing
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);  // Start time

        long long result = fibonacci_matrix(i);

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);  // End time

        // Calculate elapsed time in nanoseconds
        uint64_t time_ns = (uint64_t)(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        double time_sec = (double)time_ns / 1e9; // Convert to seconds

        // Write to CSV
        fprintf(file, "%d,%lld,%.12f,%llu\n", i, result, time_sec, time_ns);

        // Print to console
        printf("Fibonacci(%d) = %lld, Time taken: %.12f seconds (%llu ns)\n", i, result, time_sec, time_ns);
    }

    // Close the file
    fclose(file);
    printf("Results saved to fibonacci_matrix_results.csv\n");

    return 0;
}

#include <stdio.h>
#include <time.h>
#include <stdint.h>

long long binomial_coefficient(int h, int p) {
    if (p > h) {
        return 0;
    }
    if (p == 0 || p == h) {
        return 1;
    }
    if (p > h - p) {
        p = h - p;
    }
    long long result = 1;
    for (int i = 1; i <= p; i++) {
        result *= (h - i + 1);
        result /= i;
    }
    return result;
}

void fibbo_lucas(int N, long double *sum) {
    *sum = (N == 1) ? 0 : 1;  // Single-line if-else condition

    if (N == 1) return;  // Return early for N = 1

    int s = N / 2;
    int K = 2;
    for (int i = 1; i < s; i++) {
        int n = N - K - 1;
        int r = K - 1;
        int t = N - 2 * K;
        *sum += (t > r) ? binomial_coefficient(n, r) : binomial_coefficient(n, t);
        K++;
    }
}

int main() {
    int N;
    long double sum;

    // Open CSV file for writing
    FILE *file = fopen("fibbo_lucas_results.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write header to CSV file
    fprintf(file, "Index,Fibbo Lucas Sum,Execution Time (seconds),Execution Time (nanoseconds)\n");

    printf("Enter N: ");
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);  // Start time (high precision, raw clock)

        fibbo_lucas(i, &sum);

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);  // End time

        // Calculate elapsed time
        uint64_t time_ns = (uint64_t)(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        double time_sec = (double)time_ns / 1e9; // Convert to seconds

        fprintf(file, "%d,%Lf,%.12f,%llu\n", i, sum, time_sec, time_ns);
        printf("N = %d, Result: %Lf, Time taken: %.12f seconds (%llu ns)\n", i, sum, time_sec, time_ns);
    }

    // Close file
    fclose(file);
    printf("Results saved to fibbo_lucas_results.csv\n");

    return 0;
}

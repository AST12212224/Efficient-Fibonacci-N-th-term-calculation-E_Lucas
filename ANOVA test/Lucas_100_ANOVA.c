#include <stdio.h>
#include <time.h>
#include <stdint.h>

long long binomial_coefficient(int h, int p) {
    if (p > h) return 0;
    if (p == 0 || p == h) return 1;
    if (p > h - p) p = h - p;

    long long result = 1;
    for (int i = 1; i <= p; i++) {
        result *= (h - i + 1);
        result /= i;
    }
    return result;
}

void fibbo_lucas(int n, long double *sum) {
    *sum = 0;
    int S = (n - 1) / 2;  // Fix: reduce 1 from n
    for (int k = 0; k <= S; k++) {
        *sum += binomial_coefficient(n - k - 1, k);
    }
}

int main() {
    const int n = 80;
    const int trials = 20;
    long double result;

    FILE *file = fopen("lucas_n80_trials.csv", "w");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "Trial,Fibonacci_Index,Lucas_Value,Execution_Time_Seconds,Execution_Time_Nanoseconds\n");

    for (int trial = 1; trial <= trials; trial++) {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        fibbo_lucas(n, &result);

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        uint64_t time_ns = (uint64_t)(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        double time_sec = (double)time_ns / 1e9;

        fprintf(file, "%d,%d,%Lf,%.12f,%llu\n", trial, n, result, time_sec, time_ns);
        printf("Trial %d: Lucas(%d) = %Lf, Time = %.12f s (%llu ns)\n", trial, n, result, time_sec, time_ns);
    }

    fclose(file);
    return 0;
}

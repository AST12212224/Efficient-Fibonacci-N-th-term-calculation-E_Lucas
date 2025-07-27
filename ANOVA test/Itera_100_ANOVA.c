#include <stdio.h>
#include <time.h>
#include <stdint.h>

long long fibonacci_iterative(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long prev1 = 0, prev2 = 1, fib = 1;
    for (int i = 2; i <= n; i++) {
        fib = prev1 + prev2;
        prev1 = prev2;
        prev2 = fib;
    }
    return fib;
}

int main() {
    const int n = 80;
    const int trials = 20;

    FILE *file = fopen("iterative_n80_trials.csv", "w");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "Trial,Fibonacci_Index,Fibonacci_Number,Execution_Time_Seconds,Execution_Time_Nanoseconds\n");

    for (int trial = 1; trial <= trials; trial++) {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        long long result = fibonacci_iterative(n);

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        uint64_t time_ns = (uint64_t)(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        double time_sec = (double)time_ns / 1e9;

        fprintf(file, "%d,%d,%lld,%.12f,%llu\n", trial, n, result, time_sec, time_ns);
        printf("Trial %d: Fibonacci(%d) = %lld, Time = %.12f s (%llu ns)\n", trial, n, result, time_sec, time_ns);
    }

    fclose(file);
    return 0;
}

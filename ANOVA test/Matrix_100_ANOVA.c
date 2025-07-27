#include <stdio.h>
#include <time.h>
#include <stdint.h>

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

void power(long long F[2][2], long long n) {
    if (n == 0 || n == 1) return;

    long long M[2][2] = {{1, 1}, {1, 0}};
    power(F, n / 2);
    multiply(F, F);

    if (n % 2 != 0)
        multiply(F, M);
}

long long fibonacci_matrix(long long n) {
    if (n == 0) return 0;
    long long F[2][2] = {{1, 1}, {1, 0}};
    power(F, n - 1);
    return F[0][0];
}

int main() {
    const int n = 80;
    const int trials = 20;

    FILE *file = fopen("matrix_n80_trials.csv", "w");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "Trial,Fibonacci_Index,Fibonacci_Number,Execution_Time_Seconds,Execution_Time_Nanoseconds\n");

    for (int trial = 1; trial <= trials; trial++) {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        long long result = fibonacci_matrix(n);  // ✅ No +1 now

        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        uint64_t time_ns = (uint64_t)(end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        double time_sec = (double)time_ns / 1e9;

        fprintf(file, "%d,%d,%lld,%.12f,%llu\n", trial, n, result, time_sec, time_ns);
        printf("Trial %d: Fibonacci(%d) = %lld, Time = %.12f s (%llu ns)\n", trial, n, result, time_sec, time_ns);
    }

    fclose(file);
    return 0;
}

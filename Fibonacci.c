#include <stdio.h>

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
    *sum = 1;
    int s = N / 2;
    int K = 2;
    for (int i = 1; i < s; i++) {
        int n = N - K - 1;
        int r = K - 1;
        int t = N - 2 * K;
        if (t > r) {
            *sum += binomial_coefficient(n, r);
        } else {
            *sum += binomial_coefficient(n, t);
        }
        K++;
    }
}

int main() {
    int N;
    long double sum;
    printf("Enter n: ");
    scanf("%d", &N);
    fibbo_lucas(N, &sum);
    printf("Result: %Lf\n", sum);
    return 0;
}

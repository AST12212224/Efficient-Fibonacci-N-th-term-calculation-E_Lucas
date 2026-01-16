#include <stdio.h>
#include <time.h>
#include <gmp.h>

void fibonacci_lucas_gmp(unsigned long n, mpz_t result) {
    if (n == 1) {
        mpz_set_ui(result, 0);
        return;
    }
    if (n == 2) {
        mpz_set_ui(result, 1);
        return;
    }
    
    mpz_set_ui(result, 1);  // Base case
    mpz_t binom;
    mpz_init(binom);
    
    unsigned long s = n / 2;
    for (unsigned long k = 1; k <= s; k++) {
        mpz_bin_uiui(binom, n - k - 1, k);  // GMP binomial
        mpz_add(result, result, binom);
    }
    
    mpz_clear(binom);
}

int main() {
    unsigned long N;
    printf("Enter N: ");
    scanf("%lu", &N);
    
    FILE *file = fopen("lucas_gmp_results.csv", "w");
    fprintf(file, "n,Fibonacci,Time_ns\n");
    
    mpz_t fib;
    mpz_init(fib);
    
    for (unsigned long i = 1; i <= N; i++) {
        struct timespec start, end;
        
        clock_gettime(CLOCK_MONOTONIC, &start);
        fibonacci_lucas_gmp(i, fib);
        clock_gettime(CLOCK_MONOTONIC, &end);
        
        uint64_t time_ns = (end.tv_sec - start.tv_sec) * 1000000000UL + 
                          (end.tv_nsec - start.tv_nsec);
        
        gmp_fprintf(file, "%lu,%Zd,%lu\n", i, fib, time_ns);
    }
    
    mpz_clear(fib);
    fclose(file);
    return 0;
}

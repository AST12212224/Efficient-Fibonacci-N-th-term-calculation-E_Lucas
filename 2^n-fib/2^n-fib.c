#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int limit;
    unsigned long long power_of_2, fib1 = 0, fib2 = 1, fib_next;

    printf("Enter the limit: ");
    scanf("%d", &limit);

    fp = fopen("data.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write header
    fprintf(fp, "Power_of_2,Fibonacci,Diff\n");

    // Skip first two Fibonacci numbers: 0, 1
    fib_next = fib1 + fib2;  // fib_next becomes 1 (third Fibonacci number)
    fib1 = fib2;
    fib2 = fib_next;

    for (int i = 0; i < limit; i++) {
        // Calculate 2^n
        power_of_2 = 1ULL << i;

        // Write to file
        fprintf(fp, "%llu,%llu,%lld\n", power_of_2, fib_next, (long long)(power_of_2 - fib_next));

        // Move to next Fibonacci number
        fib_next = fib1 + fib2;
        fib1 = fib2;
        fib2 = fib_next;
    }

    fclose(fp);
    printf("Data written to data.csv successfully.\n");

    return 0;
}

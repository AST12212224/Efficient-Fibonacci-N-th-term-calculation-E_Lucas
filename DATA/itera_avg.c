#include <stdio.h>
#include <stdlib.h>

#define NUM_FILES 3
#define NUM_ENTRIES 200

int main() {
    char *filenames[NUM_FILES] = {"iterative_1.csv", "iterative_2.csv", "iterative_3.csv"};
    FILE *files[NUM_FILES];
    FILE *output;
    long double seconds;
    long long nanoseconds;
    long double avgSeconds;
    long long avgNanoseconds;
    int fibNumber;  // To hold the Fibonacci number which is not used
    char buffer[1024];  // Buffer for reading lines
    int i, j;

    // Open all input files
    for (i = 0; i < NUM_FILES; i++) {
        files[i] = fopen(filenames[i], "r");
        if (!files[i]) {
            fprintf(stderr, "Error opening file %s\n", filenames[i]);
            return EXIT_FAILURE;
        }
        // Read and ignore the first line (header)
        fgets(buffer, sizeof(buffer), files[i]);
    }

    // Create output file
    output = fopen("iterative_avg.csv", "w");
    if (!output) {
        fprintf(stderr, "Error creating output file\n");
        return EXIT_FAILURE;
    }

    // Write header to output file
    fprintf(output, "Index, Average Execution Time (Seconds), Average Execution Time (Nanoseconds)\n");

    // Process each entry
    for (i = 1; i <= NUM_ENTRIES; i++) {
        avgSeconds = 0.0;
        avgNanoseconds = 0;

        // Sum data from all files
        for (j = 0; j < NUM_FILES; j++) {
            if (fscanf(files[j], "%*d,%d,%Lf,%lld%*[\n]", &fibNumber, &seconds, &nanoseconds) != 3) {
                fprintf(stderr, "Error reading data from file %s on line %d\n", filenames[j], i + 1);
            } else {
                avgSeconds += seconds;
                avgNanoseconds += nanoseconds;
            }
        }

        // Calculate average
        avgSeconds /= NUM_FILES;
        avgNanoseconds /= NUM_FILES;

        // Write to output file
        fprintf(output, "%d,%.12Lf,%lld\n", i, avgSeconds, avgNanoseconds);
    }

    // Close all files
    for (i = 0; i < NUM_FILES; i++) {
        fclose(files[i]);
    }
    fclose(output);

    printf("Processing complete. Output written to iterative_avg.csv\n");

    return EXIT_SUCCESS;
}

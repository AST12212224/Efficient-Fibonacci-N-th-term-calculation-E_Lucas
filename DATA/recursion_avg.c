#include <stdio.h>
#include <stdlib.h>

#define NUM_FILES 3

int main() {
    char *filenames[NUM_FILES] = {"recursion_1.csv", "recursion_2.csv", "recursion_3.csv"};
    FILE *files[NUM_FILES];
    FILE *output;
    long double seconds;
    long long nanoseconds;
    char buffer[1024];
    int i, j;
    int entryIndex = 1; // Index for entries in the output file

    // Open all input files
    for (i = 0; i < NUM_FILES; i++) {
        files[i] = fopen(filenames[i], "r");
        if (!files[i]) {
            fprintf(stderr, "Failed to open file %s\n", filenames[i]);
            for (int k = 0; k < i; k++) {
                fclose(files[k]);
            }
            return EXIT_FAILURE;
        }
        fgets(buffer, sizeof(buffer), files[i]); // Assuming the first line is a header.
    }

    output = fopen("recursion_avg.csv", "w");
    if (!output) {
        fprintf(stderr, "Failed to create output file\n");
        for (j = 0; j < NUM_FILES; j++) {
            fclose(files[j]);
        }
        return EXIT_FAILURE;
    }
    fprintf(output, "Index, Average Execution Time (Seconds), Average Execution Time (Nanoseconds)\n");

    while (1) {
        int readCount = 0;
        long double totalSeconds = 0.0;
        long long totalNanoseconds = 0;
        for (j = 0; j < NUM_FILES; j++) {
            int result = fscanf(files[j], "%*f,%*f,%Lf,%lld", &seconds, &nanoseconds);
            if (result == 2) {
                totalSeconds += seconds;
                totalNanoseconds += nanoseconds;
                readCount++;
            } else if (result == EOF) {
                printf("Reached end of file %s\n", filenames[j]);
                break;
            } else {
                printf("Failed to read data from %s at index %d\n", filenames[j], entryIndex);
                break;
            }
        }
        if (readCount < NUM_FILES) {
            break; // Break from the while-loop
        }

        fprintf(output, "%d, %.12Lf, %lld\n", entryIndex++, totalSeconds / NUM_FILES, totalNanoseconds / NUM_FILES);
    }

    fclose(output);
    for (j = 0; j < NUM_FILES; j++) fclose(files[j]);

    printf("Processed %d entries. Output written to lucas_avg.csv\n", entryIndex - 1);
    return EXIT_SUCCESS;
}

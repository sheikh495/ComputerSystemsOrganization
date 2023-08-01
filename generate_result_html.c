#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dotprod.h"
#include "ur4_dotprod.h"
#include "ae4_dotprod.h"
#include "sse_dotprod.h"

void generate_result_html() {
    // Array sizes to test
    int array_sizes[] = {32768, 65536, 131072, 262144};

    // Number of dot product versions to test
    int num_versions = 4;

    // Allocate memory for result table
    float** result_table = (float**)malloc(num_versions * sizeof(float*));
    for (int i = 0; i < num_versions; i++) {
        result_table[i] = (float*)malloc(sizeof(float) * 4); // Four array sizes
    }

    // Run and measure execution times for each dot product version
    for (int i = 0; i < num_versions; i++) {
        for (int j = 0; j < 4; j++) {
            int n = array_sizes[j];
            float* x = (float*)malloc(sizeof(float) * n);
            float* y = (float*)malloc(sizeof(float) * n);

            // Initialize arrays x and y with random values
            for (int k = 0; k < n; k++) {
                x[k] = (float)rand() / RAND_MAX; // Random float between 0 and 1
                y[k] = (float)rand() / RAND_MAX;
            }

            // Measure execution time for the current dot product version
            clock_t start_time = clock();
            float result;

            switch (i) {
                case 0:
                    result = dotprod(x, y, n);
                    break;
                case 1:
                    result = ur4_dotprod(x, y, n);
                    break;
                case 2:
                    result = ae4_dotprod(x, y, n);
                    break;
                case 3:
                    result = sse_dotprod(x, y, n);
                    break;
            }

            clock_t end_time = clock();
            float execution_time = (float)(end_time - start_time) / CLOCKS_PER_SEC;

            // Store the execution time in the result table
            result_table[i][j] = execution_time;

            // Free memory for arrays x and y
            free(x);
            free(y);
        }
    }

    // Create and write the result table to the HTML file
    FILE* fp = fopen("result_htm.html", "w");
    if (fp == NULL) {
        printf("Error creating result_htm.html\n");
        return;
    }

    // Write the table header to the HTML file
    fprintf(fp, "<table border='1'>\n");
    fprintf(fp, "<tr><th>Array Size</th><th>dotprod</th><th>ur4_dotprod</th><th>ae4_dotprod</th><th>sse_dotprod</th></tr>\n");

    // Write the data rows to the HTML file
    for (int j = 0; j < 4; j++) {
        fprintf(fp, "<tr><td>%d</td>", array_sizes[j]);
        for (int i = 0; i < num_versions; i++) {
            fprintf(fp, "<td>%.6f</td>", result_table[i][j]);
        }
        fprintf(fp, "</tr>\n");
    }

    // Close the HTML file and free memory
    fprintf(fp, "</table>\n");
    fclose(fp);

    for (int i = 0; i < num_versions; i++) {
        free(result_table[i]);
    }
    free(result_table);

    printf("result_htm.html generated successfully.\n");
}

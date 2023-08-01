#include "ur4_dotprod.h"

float ur4_dotprod(float x[], float y[], int n) {
    // Ensure that n is divisible by 4
    int n_aligned = n - (n % 4);

    // Initialize accumulators for each set of four elements
    float sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, sum4 = 0.0;

    // Unrolled loop with four multiplications and additions per iteration
    for (int i = 0; i < n_aligned; i += 4) {
        sum1 += x[i] * y[i];
        sum2 += x[i + 1] * y[i + 1];
        sum3 += x[i + 2] * y[i + 2];
        sum4 += x[i + 3] * y[i + 3];
    }

    // Combine the partial sums
    float result = sum1 + sum2 + sum3 + sum4;

    // Calculate remaining elements (if any) using the regular dot product
    for (int i = n_aligned; i < n; i++) {
        result += x[i] * y[i];
    }

    return result;
}

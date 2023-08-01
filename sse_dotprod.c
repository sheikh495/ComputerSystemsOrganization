#include "sse_dotprod.h"
#include <emmintrin.h>

float sse_dotprod(float x[], float y[], int n) {
    // Ensure that n is divisible by 4
    int n_aligned = n - (n % 4);

    // Initialize the accumulator with zeros
    __m128 acc = _mm_setzero_ps();

    // Process four elements at a time using SSE intrinsics
    for (int i = 0; i < n_aligned; i += 4) {
        // Load four elements from arrays into SSE registers
        __m128 xmm_x = _mm_load_ps(&x[i]);
        __m128 xmm_y = _mm_load_ps(&y[i]);

        // Perform the dot product operation using SIMD instructions
        __m128 xmm_prod = _mm_mul_ps(xmm_x, xmm_y);

        // Accumulate the dot product results
        acc = _mm_add_ps(acc, xmm_prod);
    }

    // Extract the four dot product values from the accumulator
    float dotprod[4];
    _mm_store_ps(dotprod, acc);

    // Sum the four dot product values
    float result = dotprod[0] + dotprod[1] + dotprod[2] + dotprod[3];

    // Calculate remaining elements (if any) using the regular dot product
    for (int i = n_aligned; i < n; i++) {
        result += x[i] * y[i];
    }

    return result;
}

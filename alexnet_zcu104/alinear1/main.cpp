#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hls_math.h"

float relu(float x) {
    return x > 0 ? x : 0.0;
}

void dense1(
    float inputs[9216], float weights[4096 * 9216], float bias[4096],
    float final[4096]
) {
#pragma HLS INTERFACE m_axi port=inputs depth=9216 offset=slave
#pragma HLS INTERFACE m_axi port=weights depth=4096*9216 offset=slave
#pragma HLS INTERFACE m_axi port=bias depth=4096 offset=slave
#pragma HLS INTERFACE m_axi port=final depth=4096 offset=slave
#pragma HLS INTERFACE s_axilite port=return

    for (int j = 0; j < 4096; j++) {
        float sum = 0.0;  // Initialize sum with the bias
        for (int i = 0; i < 9216; i++) {
            sum += inputs[i] * weights[j * 9216 + i];
        }
        final[j] = relu(sum +bias[j]);  // Apply ReLU to the sum
    }
}

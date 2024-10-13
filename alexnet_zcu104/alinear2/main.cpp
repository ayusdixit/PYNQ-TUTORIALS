#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hls_math.h"

float relu(float x) {
    return x > 0 ? x : 0.0;
}

void linear2(
    float inputs[4096], float weights[4096 * 4096], float bias[4096],
    float final[4096]
)
{
#pragma HLS INTERFACE m_axi port=inputs depth=4096 offset=slave
#pragma HLS INTERFACE m_axi port=weights depth=4096*4096 offset=slave
#pragma HLS INTERFACE m_axi port=bias depth=4096 offset=slave
#pragma HLS INTERFACE m_axi port=final depth=4096 offset=slave
#pragma HLS INTERFACE s_axilite port=return

    float sum;

    // Compute dense layer output on the fly for 4096 output neurons
    for (int j = 0; j < 4096; j++) {
        sum = 0.0;
        for (int i = 0; i < 4096; i++) {
            // Access the 1D weights array as if it were a 2D array
            sum += inputs[i] * weights[j * 4096 + i];
        }
        final[j] = relu(sum + bias[j]);  // Store the final output directly
    }
}

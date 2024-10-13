#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hls_math.h"

//float relu(float x) {
//    return x > 0 ? x : 0.0;
//}

void dense_layer(
    float inputs[4096], float weights[2 * 4096], float bias[2],
    float final[2]
)
{
#pragma HLS INTERFACE m_axi port=inputs depth=4096 offset=slave
#pragma HLS INTERFACE m_axi port=weights depth=2*4096 offset=slave
#pragma HLS INTERFACE m_axi port=bias depth=2 offset=slave
#pragma HLS INTERFACE m_axi port=final depth=2 offset=slave
#pragma HLS INTERFACE s_axilite port=return

    float sum;

    // Compute dense layer output on the fly for 2 output neurons
    for (int j = 0; j < 2; j++) {
        sum = 0.0;
        for (int i = 0; i < 4096; i++) {
             // Access the 1D weights array as if it were a 2D array
            sum += inputs[i] * weights[j * 4096 + i];
        }
        final[j] = (sum + bias[j]);  // Store the final output directly
    }
}

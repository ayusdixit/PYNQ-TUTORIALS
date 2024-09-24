#include "dense1.h"
#include "dense2.h"
#include "dense3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hls_math.h"


float relu(float x) {
    return x > 0 ? x : 0.0;
}


void softmax(float x[], float y[], int size) {
    float max_x = x[0], sum = 0.0;

    for (int i = 1; i < size; i++) {
        if (x[i] > max_x) {
            max_x = x[i];
        }
    }

    for (int i = 0; i < size; i++) {
        y[i] = hls::exp(x[i] - max_x);
        sum += y[i];
    }

    for (int i = 0; i < size; i++) {
        y[i] /= sum;
    }
}







void dense_layer(
    float inputs[256],
    float final[10]
)
{
#pragma HLS INTERFACE m_axi port=inputs depth=256 offset=slave
#pragma HLS INTERFACE m_axi port=final depth=10 offset=slave

#pragma HLS INTERFACE s_axilite port=return

    float input_buffer[1][256];
    float output_buffer[1][120];
    float final_buffer[1][84];
    float last_buffer[1][10];

    // Convert 1D input to 2D input_buffer
    for (int i = 0; i < 256; ++i) {
        input_buffer[0][i] = inputs[i];
    }

    // Compute first dense layer output
    for (int j = 0; j < 120; j++) {
        float sum = 0.0;
        for (int i = 0; i < 256; i++) {
            sum += input_buffer[0][i] * weights[j][i];
        }
        output_buffer[0][j] = relu(sum + bias[j]);
    }

    // Compute second dense layer output
    for (int j = 0; j < 84; j++) {
        float sum1 = 0.0;
        for (int i = 0; i < 120; i++) {
            sum1 += output_buffer[0][i] * weights_2[j][i];
        }
        final_buffer[0][j] = sum1 + bias_2[j];
    }
    // Compute third dense layer output
        for (int j = 0; j < 10; j++) {
            float sum = 0.0;
            for (int i = 0; i < 84; i++) {
                sum += final_buffer[0][i] * weights_3[j][i];
            }
            last_buffer[0][j] = sum + bias_3[j];
        }

    // Convert 2D output_buffer to 1D output
    for (int j = 0; j < 10; ++j) {
        final[j] = last_buffer[0][j];
    }
}

#include "conv1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE (1*1*28*28)
#define CONV_OUTPUT_SIZE (1*6*24*24)
#define FINAL_OUTPUT_SIZE (1*6*12*12)
#define KERNEL_SIZE 5

float relu(float x) {
    return x > 0 ? x : 0.0;
}

float max(float a, float b, float c, float d) {
    float m = a;
    if (b > m) m = b;
    if (c > m) m = c;
    if (d > m) m = d;
    return m;
}

void conv1(
    float input[784],
    float final_buffer[864]
)
{
#pragma HLS INTERFACE m_axi port=input depth=INPUT_SIZE offset=slave
#pragma HLS INTERFACE m_axi port=final_buffer depth=FINAL_OUTPUT_SIZE offset=slave
#pragma HLS INTERFACE s_axilite port=return

    float input_buffer[1][1][28][28];
    float output_buffer[1][6][24][24];

    // Convert 1D input to 4D input_buffer
    for (int h = 0; h < 28; h++) {
        for (int w = 0; w < 28; w++) {
            input_buffer[0][0][h][w] = input[h*28 + w];
        }
    }

    // Perform convolution
    for (int oc = 0; oc < 6; oc++) {
        for (int oh = 0; oh < 24; oh++) {
            for (int ow = 0; ow < 24; ow++) {
                float sum = 0.0;
                for (int kh = 0; kh < 5; kh++) {
                    for (int kw = 0; kw < 5; kw++) {
                        int ih = oh + kh;
                        int iw = ow + kw;
                        sum += input_buffer[0][0][ih][iw] * conv1_weights[oc][0][kh][kw];
                    }
                }
                sum += conv1_bias[oc];
                output_buffer[0][oc][oh][ow] = relu(sum);
            }
        }
    }

    // Perform max pooling and store in final_buffer
    int final_idx = 0;
    for (int c = 0; c < 6; c++) {
        for (int h = 0; h < 12; h++) {
            for (int w = 0; w < 12; w++) {
                float pool_val = max(
                    output_buffer[0][c][h*2][w*2],
                    output_buffer[0][c][h*2][w*2+1],
                    output_buffer[0][c][h*2+1][w*2],
                    output_buffer[0][c][h*2+1][w*2+1]
                );
                final_buffer[final_idx++] = pool_val;
            }
        }
    }
}

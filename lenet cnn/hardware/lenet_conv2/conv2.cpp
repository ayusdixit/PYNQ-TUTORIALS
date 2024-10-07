#include "conv2.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE (1*6*12*12)
#define OUTPUT_SIZE (1*16*8*8)
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
void conv2(
    float input[864],
	 float final_buffer[256]
)
{
#pragma HLS INTERFACE m_axi port=input depth=INPUT_SIZE offset=slave
#pragma HLS INTERFACE m_axi port=final_buffer depth=OUTPUT_SIZE offset=slave
#pragma HLS INTERFACE s_axilite port=return

    float input_buffer[1][6][12][12];
    float output_buffer[1][16][8][8];

    // Convert 1D input to 4D input_buffer
    for (int c = 0; c < 6; c++) {
        for (int h = 0; h < 12; h++) {
            for (int w = 0; w < 12; w++) {
                input_buffer[0][c][h][w] = input[c*12*12 + h*12 + w];
            }
        }
    }

    // Perform convolution
    for (int oc = 0; oc < 16; oc++) {
        for (int oh = 0; oh < 8; oh++) {
            for (int ow = 0; ow < 8; ow++) {
                float sum = 0.0;
                for (int ic = 0; ic < 6; ic++) {
                    for (int kh = 0; kh < 5; kh++) {
                        for (int kw = 0; kw < 5; kw++) {
                            int ih = oh + kh;
                            int iw = ow + kw;
                            if (ih < 12 && iw < 12) {
                                sum += input_buffer[0][ic][ih][iw] * conv2_weights[oc][ic][kh][kw];
                            }
                        }
                    }
                }
                sum += conv2_bias[oc];
                output_buffer[0][oc][oh][ow] = relu(sum);
            }
        }
    }

    // Perform max pooling and store in final_buffer
        int final_idx = 0;
        for (int c = 0; c < 16; c++) {
            for (int h = 0; h < 4; h++) {
                for (int w = 0; w < 4; w++) {
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

#include "lenet.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void lenet(
    float input[784],    // 1 * 1 * 28 * 28
    float output[3456]   // 1 * 6 * 24 * 24
)
{
#pragma HLS INTERFACE m_axi port=input depth=784 offset=slave bundle=gmem0
#pragma HLS INTERFACE m_axi port=output depth=3456 offset=slave bundle=gmem1
#pragma HLS INTERFACE s_axilite port=return

    float input_buffer[1][1][28][28];
    float output_buffer[1][6][24][24];

    // Copy input to buffer
    for (int h = 0; h < 28; ++h) {
        for (int w = 0; w < 28; ++w) {
            input_buffer[0][0][h][w] = input[h * 28 + w];
        }
    }

    // Perform 2D convolution
    for (int n = 0; n < 1; ++n) {
        for (int oc = 0; oc < 6; ++oc) {
            for (int oh = 0; oh < 24; ++oh) {
                for (int ow = 0; ow < 24; ++ow) {
                    float sum = 0.0;
                    for (int ic = 0; ic < 1; ++ic) {
                        for (int kh = 0; kh < 5; ++kh) {
                            for (int kw = 0; kw < 5; ++kw) {
                                int ih = oh + kh;
                                int iw = ow + kw;
                                sum += input_buffer[n][ic][ih][iw] * Conv1_Weights[oc][ic][kh][kw];
                            }
                        }
                    }
                    output_buffer[n][oc][oh][ow] = sum + Conv1_bias[oc];
                }
            }
        }
    }

    // Copy output buffer to output
    for (int oc = 0; oc < 6; ++oc) {
        for (int oh = 0; oh < 24; ++oh) {
            for (int ow = 0; ow < 24; ++ow) {
                output[(oc * 24 * 24) + (oh * 24) + ow] = output_buffer[0][oc][oh][ow];
            }
        }
    }
}

//#include "conv1.h"
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//#define INPUT_SIZE (1*3*224*224)
//#define CONV_OUTPUT_SIZE (1*64*55*55)
//#define WEIGHT_SIZE (64*3*11*11)
//#define KERNEL_SIZE 11
//#define STRIDE 4
//#define PADDING 2
//
//float relu(float x) {
//    return x > 0 ? x : 0.0;
//}
//
//void conv1(
//    float input[INPUT_SIZE],
//    float weights[WEIGHT_SIZE],
//     float output[CONV_OUTPUT_SIZE]
//)
//{
//#pragma HLS INTERFACE m_axi port=input depth=INPUT_SIZE offset=slave
//#pragma HLS INTERFACE m_axi port=weights depth=WEIGHT_SIZE offset=slave
// #pragma HLS INTERFACE m_axi port=output depth=CONV_OUTPUT_SIZE offset=slave
//#pragma HLS INTERFACE s_axilite port=return
//
//    float input_buffer[1][3][224][224];
//    float weight_buffer[64][3][11][11];
//    float output_buffer[1][64][55][55];
//
//    // Convert 1D input to 4D input_buffer
//    for (int c = 0; c < 3; c++) {
//        for (int h = 0; h < 224; h++) {
//            for (int w = 0; w < 224; w++) {
//                input_buffer[0][c][h][w] = input[c*224*224 + h*224 + w];
//            }
//        }
//    }
//
//    // Convert 1D weights to 4D weight_buffer
//    for (int oc = 0; oc < 64; oc++) {
//        for (int ic = 0; ic < 3; ic++) {
//            for (int kh = 0; kh < 11; kh++) {
//                for (int kw = 0; kw < 11; kw++) {
//                    weight_buffer[oc][ic][kh][kw] = weights[oc*3*11*11 + ic*11*11 + kh*11 + kw];
//                }
//            }
//        }
//    }
//
//    // Perform convolution
//    for (int oc = 0; oc < 64; oc++) {
//        for (int oh = 0; oh < 55; oh++) {
//            for (int ow = 0; ow < 55; ow++) {
//                float sum = 0.0;
//                for (int ic = 0; ic < 3; ic++) {
//                    for (int kh = 0; kh < KERNEL_SIZE; kh++) {
//                        for (int kw = 0; kw < KERNEL_SIZE; kw++) {
//                            int ih = oh * STRIDE + kh - PADDING;
//                            int iw = ow * STRIDE + kw - PADDING;
//                            if (ih >= 0 && ih < 224 && iw >= 0 && iw < 224) {
//                                sum += input_buffer[0][ic][ih][iw] * weight_buffer[oc][ic][kh][kw];
//                            }
//                        }
//                    }
//                }
//                sum += conv1_bias[oc];
//                output_buffer[0][oc][oh][ow] = relu(sum);
//            }
//        }
//    }
//
//    // Convert 4D output_buffer to 1D output
//    for (int oc = 0; oc < 64; oc++) {
//        for (int oh = 0; oh < 55; oh++) {
//            for (int ow = 0; ow < 55; ow++) {
//                output[oc*55*55 + oh*55 + ow] = output_buffer[0][oc][oh][ow];
//            }
//        }
//    }
//}


////////////////////////////////////////code 2 ------------
//#include "conv1.h"
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//#define INPUT_SIZE (1*3*224*224)
//#define CONV_OUTPUT_SIZE (1*64*55*55)
//#define WEIGHT_SIZE (64*3*11*11)
//#define KERNEL_SIZE 11
//#define STRIDE 4
//#define PADDING 2
//
//float relu(float x) {
//    return x > 0 ? x : 0.0;
//}
//
//void conv1(
//    float input[INPUT_SIZE],
//    float weights[WEIGHT_SIZE],
//    float output[CONV_OUTPUT_SIZE],
//    float bias[64]
//)
//{
//#pragma HLS INTERFACE m_axi port=input depth=INPUT_SIZE offset=slave
//#pragma HLS INTERFACE m_axi port=weights depth=WEIGHT_SIZE offset=slave
//#pragma HLS INTERFACE m_axi port=output depth=CONV_OUTPUT_SIZE offset=slave
//#pragma HLS INTERFACE m_axi port=bias depth=64 offset=slave
//#pragma HLS INTERFACE s_axilite port=return
//
//    // Perform convolution
//    for (int oc = 0; oc < 64; oc++) {
//        for (int oh = 0; oh < 55; oh++) {
//            for (int ow = 0; ow < 55; ow++) {
//                float sum = 0.0;
//                for (int ic = 0; ic < 3; ic++) {
//                    for (int kh = 0; kh < KERNEL_SIZE; kh++) {
//                        for (int kw = 0; kw < KERNEL_SIZE; kw++) {
//                            int ih = oh * STRIDE + kh - PADDING;
//                            int iw = ow * STRIDE + kw - PADDING;
//                            if (ih >= 0 && ih < 224 && iw >= 0 && iw < 224) {
//                                int input_index = ic * 224 * 224 + ih * 224 + iw;
//                                int weight_index = oc * 3 * 11 * 11 + ic * 11 * 11 + kh * 11 + kw;
//                                sum += input[input_index] * weights[weight_index];
//                            }
//                        }
//                    }
//                }
//                sum += bias[oc];
//                int output_index = oc * 55 * 55 + oh * 55 + ow;
//                output[output_index] = relu(sum);
//            }
//        }
//    }
//}
/////////////////////////////////////////////////code 3
//#include "conv1.h"
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//#define INPUT_SIZE (1*3*224*224)
//#define CONV_OUTPUT_SIZE (1*64*55*55)
//#define WEIGHT_SIZE (64*3*11*11)
//#define KERNEL_SIZE 11
//#define STRIDE 4
//#define PADDING 2
//
//// Define smaller buffer sizes
//#define INPUT_CHUNK_HEIGHT 14
//#define INPUT_CHUNK_WIDTH 56
//#define OUTPUT_CHUNK_HEIGHT 4
//#define OUTPUT_CHUNK_WIDTH 14
//#define WEIGHT_CHUNK_OC 16
//
//float relu(float x) {
//    return x > 0 ? x : 0.0;
//}
//
//void conv1(
//    float input[INPUT_SIZE],
//    float weights[WEIGHT_SIZE],
//    float output[CONV_OUTPUT_SIZE]
//)
//{
//#pragma HLS INTERFACE m_axi port=input depth=INPUT_SIZE offset=slave
//#pragma HLS INTERFACE m_axi port=weights depth=WEIGHT_SIZE offset=slave
//#pragma HLS INTERFACE m_axi port=output depth=CONV_OUTPUT_SIZE offset=slave
//#pragma HLS INTERFACE s_axilite port=return
//
//    float input_buffer[3][INPUT_CHUNK_HEIGHT][INPUT_CHUNK_WIDTH];
//    float weight_buffer[WEIGHT_CHUNK_OC][3][KERNEL_SIZE][KERNEL_SIZE];
//    float output_buffer[WEIGHT_CHUNK_OC][OUTPUT_CHUNK_HEIGHT][OUTPUT_CHUNK_WIDTH];
//
//    // Process input in chunks
//    for (int h_start = 0; h_start < 224; h_start += INPUT_CHUNK_HEIGHT) {
//        for (int w_start = 0; w_start < 224; w_start += INPUT_CHUNK_WIDTH) {
//            // Load input chunk
//            for (int c = 0; c < 3; c++) {
//                for (int h = 0; h < INPUT_CHUNK_HEIGHT && h + h_start < 224; h++) {
//                    for (int w = 0; w < INPUT_CHUNK_WIDTH && w + w_start < 224; w++) {
//                        input_buffer[c][h][w] = input[c*224*224 + (h_start+h)*224 + (w_start+w)];
//                    }
//                }
//            }
//
//            // Process output channels in chunks
//            for (int oc_start = 0; oc_start < 64; oc_start += WEIGHT_CHUNK_OC) {
//                // Load weight chunk
//                for (int oc = 0; oc < WEIGHT_CHUNK_OC && oc + oc_start < 64; oc++) {
//                    for (int ic = 0; ic < 3; ic++) {
//                        for (int kh = 0; kh < KERNEL_SIZE; kh++) {
//                            for (int kw = 0; kw < KERNEL_SIZE; kw++) {
//                                weight_buffer[oc][ic][kh][kw] = weights[(oc_start+oc)*3*KERNEL_SIZE*KERNEL_SIZE + ic*KERNEL_SIZE*KERNEL_SIZE + kh*KERNEL_SIZE + kw];
//                            }
//                        }
//                    }
//                }
//
//                // Initialize output buffer
//                for (int oc = 0; oc < WEIGHT_CHUNK_OC; oc++) {
//                    for (int oh = 0; oh < OUTPUT_CHUNK_HEIGHT; oh++) {
//                        for (int ow = 0; ow < OUTPUT_CHUNK_WIDTH; ow++) {
//                            output_buffer[oc][oh][ow] = 0.0f;
//                        }
//                    }
//                }
//
//                // Perform convolution on the chunk
//                for (int oc = 0; oc < WEIGHT_CHUNK_OC && oc + oc_start < 64; oc++) {
//                    for (int oh = 0; oh < OUTPUT_CHUNK_HEIGHT; oh++) {
//                        for (int ow = 0; ow < OUTPUT_CHUNK_WIDTH; ow++) {
//                            float sum = 0.0;
//                            for (int ic = 0; ic < 3; ic++) {
//                                for (int kh = 0; kh < KERNEL_SIZE; kh++) {
//                                    for (int kw = 0; kw < KERNEL_SIZE; kw++) {
//                                        int ih = oh * STRIDE + kh - PADDING;
//                                        int iw = ow * STRIDE + kw - PADDING;
//                                        if (ih >= 0 && ih < INPUT_CHUNK_HEIGHT && iw >= 0 && iw < INPUT_CHUNK_WIDTH) {
//                                            sum += input_buffer[ic][ih][iw] * weight_buffer[oc][ic][kh][kw];
//                                        }
//                                    }
//                                }
//                            }
//                            sum += conv1_bias[oc + oc_start];
//                            output_buffer[oc][oh][ow] = relu(sum);
//                        }
//                    }
//                }
//
//                // Write output chunk to global memory
//                for (int oc = 0; oc < WEIGHT_CHUNK_OC && oc + oc_start < 64; oc++) {
//                    for (int oh = 0; oh < OUTPUT_CHUNK_HEIGHT; oh++) {
//                        for (int ow = 0; ow < OUTPUT_CHUNK_WIDTH; ow++) {
//                            int output_h = h_start / STRIDE + oh;
//                            int output_w = w_start / STRIDE + ow;
//                            if (output_h < 55 && output_w < 55) {
//                                output[(oc+oc_start)*55*55 + output_h*55 + output_w] = output_buffer[oc][oh][ow];
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//}
////////////////////////////////////////////////////////////////////code 4 wroking but oberrutilizairon
//#include "conv1.h"
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//#define INPUT_SIZE (1*3*224*224)
//#define CONV_OUTPUT_SIZE (1*64*55*55)
//#define WEIGHT_SIZE (64*3*11*11)
//#define KERNEL_SIZE 11
//#define STRIDE 4
//#define PADDING 2
//#define POOL_KERNEL_SIZE 3
//#define POOL_STRIDE 2
//
//// Define smaller buffer sizes
//#define INPUT_CHUNK_HEIGHT 28
//#define INPUT_CHUNK_WIDTH 112
//#define OUTPUT_CHUNK_HEIGHT 7
//#define OUTPUT_CHUNK_WIDTH 28
//#define WEIGHT_CHUNK_OC 16
//#define POOL_OUTPUT_HEIGHT 27
//#define POOL_OUTPUT_WIDTH 27
//
//float relu(float x) {
//    return x > 0 ? x : 0.0;
//}
//
//float max9(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
//    float m = a;
//    if (b > m) m = b;
//    if (c > m) m = c;
//    if (d > m) m = d;
//    if (e > m) m = e;
//    if (f > m) m = f;
//    if (g > m) m = g;
//    if (h > m) m = h;
//    if (i > m) m = i;
//    return m;
//}
//
//void conv1(
//    float input[INPUT_SIZE],
//    float weights[WEIGHT_SIZE],
//    float output[64*POOL_OUTPUT_HEIGHT*POOL_OUTPUT_WIDTH]
//)
//{
//#pragma HLS INTERFACE m_axi port=input depth=INPUT_SIZE offset=slave
//#pragma HLS INTERFACE m_axi port=weights depth=WEIGHT_SIZE offset=slave
//#pragma HLS INTERFACE m_axi port=output depth=64*POOL_OUTPUT_HEIGHT*POOL_OUTPUT_WIDTH offset=slave
//#pragma HLS INTERFACE s_axilite port=return
//
//    float input_buffer[3][INPUT_CHUNK_HEIGHT][INPUT_CHUNK_WIDTH];
//    float weight_buffer[WEIGHT_CHUNK_OC][3][KERNEL_SIZE][KERNEL_SIZE];
//    float conv_output[64][55][55];
//
//    // Convolution
//    for (int h_start = 0; h_start < 224; h_start += INPUT_CHUNK_HEIGHT) {
//        for (int w_start = 0; w_start < 224; w_start += INPUT_CHUNK_WIDTH) {
//            // Load input chunk
//            for (int c = 0; c < 3; c++) {
//                for (int h = 0; h < INPUT_CHUNK_HEIGHT && h + h_start < 224; h++) {
//                    for (int w = 0; w < INPUT_CHUNK_WIDTH && w + w_start < 224; w++) {
//                        input_buffer[c][h][w] = input[c*224*224 + (h_start+h)*224 + (w_start+w)];
//                    }
//                }
//            }
//
//            // Process output channels in chunks
//            for (int oc_start = 0; oc_start < 64; oc_start += WEIGHT_CHUNK_OC) {
//                // Load weight chunk
//                for (int oc = 0; oc < WEIGHT_CHUNK_OC && oc + oc_start < 64; oc++) {
//                    for (int ic = 0; ic < 3; ic++) {
//                        for (int kh = 0; kh < KERNEL_SIZE; kh++) {
//                            for (int kw = 0; kw < KERNEL_SIZE; kw++) {
//                                weight_buffer[oc][ic][kh][kw] = weights[(oc_start+oc)*3*KERNEL_SIZE*KERNEL_SIZE + ic*KERNEL_SIZE*KERNEL_SIZE + kh*KERNEL_SIZE + kw];
//                            }
//                        }
//                    }
//                }
//
//                // Perform convolution on the chunk
//                for (int oc = 0; oc < WEIGHT_CHUNK_OC && oc + oc_start < 64; oc++) {
//                    for (int oh = 0; oh < OUTPUT_CHUNK_HEIGHT; oh++) {
//                        for (int ow = 0; ow < OUTPUT_CHUNK_WIDTH; ow++) {
//                            float sum = 0.0;
//                            for (int ic = 0; ic < 3; ic++) {
//                                for (int kh = 0; kh < KERNEL_SIZE; kh++) {
//                                    for (int kw = 0; kw < KERNEL_SIZE; kw++) {
//                                        int ih = oh * STRIDE + kh - PADDING;
//                                        int iw = ow * STRIDE + kw - PADDING;
//                                        if (ih >= 0 && ih < INPUT_CHUNK_HEIGHT && iw >= 0 && iw < INPUT_CHUNK_WIDTH) {
//                                            sum += input_buffer[ic][ih][iw] * weight_buffer[oc][ic][kh][kw];
//                                        }
//                                    }
//                                }
//                            }
//                            sum += conv1_bias[oc + oc_start];
//                            int out_h = h_start / STRIDE + oh;
//                            int out_w = w_start / STRIDE + ow;
//                            if (out_h < 55 && out_w < 55) {
//                                conv_output[oc + oc_start][out_h][out_w] = relu(sum);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    // Max Pooling
//    for (int c = 0; c < 64; c++) {
//        for (int h = 0; h < POOL_OUTPUT_HEIGHT; h++) {
//            for (int w = 0; w < POOL_OUTPUT_WIDTH; w++) {
//                float pool_val = max9(
//                    conv_output[c][h*2][w*2],
//                    conv_output[c][h*2][w*2+1],
//                    conv_output[c][h*2][w*2+2],
//                    conv_output[c][h*2+1][w*2],
//                    conv_output[c][h*2+1][w*2+1],
//                    conv_output[c][h*2+1][w*2+2],
//                    conv_output[c][h*2+2][w*2],
//                    conv_output[c][h*2+2][w*2+1],
//                    conv_output[c][h*2+2][w*2+2]
//                );
//                output[c*POOL_OUTPUT_HEIGHT*POOL_OUTPUT_WIDTH + h*POOL_OUTPUT_WIDTH + w] = pool_val;
//            }
//        }
//    }
//}
////////////////////////////////////////////////////////////////////////////////////////////code 6
#include "conv1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE (1*3*224*224)
#define WEIGHT_SIZE (64*3*11*11)
#define KERNEL_SIZE 11
#define STRIDE 4
#define PADDING 2
#define POOL_KERNEL_SIZE 3
#define POOL_STRIDE 2

#define INPUT_CHUNK_HEIGHT 36  // Keep this the same to maintain functionality
#define INPUT_CHUNK_WIDTH 224  // Keep this the same to maintain functionality
#define CONV_OUTPUT_HEIGHT 9   // (36 - 11 + 2*2) / 4 + 1
#define CONV_OUTPUT_WIDTH 55   // (224 - 11 + 2*2) / 4 + 1
#define WEIGHT_CHUNK_OC 16
#define POOL_OUTPUT_HEIGHT 27
#define POOL_OUTPUT_WIDTH 27

float relu(float x) {
    return x > 0 ? x : 0.0;
}

float max9(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    float m = a;
    if (b > m) m = b;
    if (c > m) m = c;
    if (d > m) m = d;
    if (e > m) m = e;
    if (f > m) m = f;
    if (g > m) m = g;
    if (h > m) m = h;
    if (i > m) m = i;
    return m;
}

void conv1(
    float input[INPUT_SIZE],
    float weights[WEIGHT_SIZE],
    float output[64*POOL_OUTPUT_HEIGHT*POOL_OUTPUT_WIDTH]
)
{
#pragma HLS INTERFACE m_axi port=input depth=INPUT_SIZE offset=slave
#pragma HLS INTERFACE m_axi port=weights depth=WEIGHT_SIZE offset=slave
#pragma HLS INTERFACE m_axi port=output depth=64*POOL_OUTPUT_HEIGHT*POOL_OUTPUT_WIDTH offset=slave
#pragma HLS INTERFACE s_axilite port=return


    float input_buffer[3][INPUT_CHUNK_HEIGHT][INPUT_CHUNK_WIDTH];
    float weight_buffer[WEIGHT_CHUNK_OC][3][KERNEL_SIZE][KERNEL_SIZE];
    float conv_output_buffer[WEIGHT_CHUNK_OC][CONV_OUTPUT_HEIGHT][CONV_OUTPUT_WIDTH];
#pragma HLS bind_storage variable=input type=RAM_1P
#pragma HLS bind_storage variable=weights type=RAM_1P
#pragma HLS bind_storage variable=output type=RAM_1P
     // Initialize output buffer
    for (int c = 0; c < 64; c++) {
        for (int h = 0; h < POOL_OUTPUT_HEIGHT; h++) {
            for (int w = 0; w < POOL_OUTPUT_WIDTH; w++) {
                output[c*POOL_OUTPUT_HEIGHT*POOL_OUTPUT_WIDTH + h*POOL_OUTPUT_WIDTH + w] = -3.402823466e+38F;  // Min float value
            }
        }
    }

    // Process input in overlapping chunks
    for (int h_start = 0; h_start < 224; h_start += (INPUT_CHUNK_HEIGHT - 2*POOL_KERNEL_SIZE)) {
        // Load input chunk
        for (int c = 0; c < 3; c++) {
            for (int h = 0; h < INPUT_CHUNK_HEIGHT && h + h_start < 224; h++) {
                for (int w = 0; w < INPUT_CHUNK_WIDTH; w++) {
                    int global_h = h_start + h;
                    if (global_h < 224) {
                        input_buffer[c][h][w] = input[c*224*224 + global_h*224 + w];
                    } else {
                        input_buffer[c][h][w] = 0;  // Zero padding
                    }
                }
            }
        }

        // Process output channels in chunks
        for (int oc_start = 0; oc_start < 64; oc_start += WEIGHT_CHUNK_OC) {
            // Load weight chunk
            for (int oc = 0; oc < WEIGHT_CHUNK_OC && oc + oc_start < 64; oc++) {
                for (int ic = 0; ic < 3; ic++) {
                    for (int kh = 0; kh < KERNEL_SIZE; kh++) {
                        for (int kw = 0; kw < KERNEL_SIZE; kw++) {
                            weight_buffer[oc][ic][kh][kw] = weights[(oc_start+oc)*3*KERNEL_SIZE*KERNEL_SIZE + ic*KERNEL_SIZE*KERNEL_SIZE + kh*KERNEL_SIZE + kw];
                        }
                    }
                }
            }

            // Perform convolution on the chunk
            for (int oc = 0; oc < WEIGHT_CHUNK_OC && oc + oc_start < 64; oc++) {
                for (int oh = 0; oh < CONV_OUTPUT_HEIGHT; oh++) {
                    for (int ow = 0; ow < CONV_OUTPUT_WIDTH; ow++) {
                        float sum = 0.0;
                        for (int ic = 0; ic < 3; ic++) {
                            for (int kh = 0; kh < KERNEL_SIZE; kh++) {
                                for (int kw = 0; kw < KERNEL_SIZE; kw++) {
                                    int ih = oh * STRIDE + kh - PADDING;
                                    int iw = ow * STRIDE + kw - PADDING;
                                    if (ih >= 0 && ih < INPUT_CHUNK_HEIGHT && iw >= 0 && iw < INPUT_CHUNK_WIDTH) {
                                        sum += input_buffer[ic][ih][iw] * weight_buffer[oc][ic][kh][kw];
                                    }
                                }
                            }
                        }
                        sum += conv1_bias[oc + oc_start];
                        conv_output_buffer[oc][oh][ow] = relu(sum);
                    }
                }
            }

            // Perform max pooling on the convolution output
            for (int oc = 0; oc < WEIGHT_CHUNK_OC && oc + oc_start < 64; oc++) {
                for (int oh = 0; oh < CONV_OUTPUT_HEIGHT - POOL_KERNEL_SIZE + 1; oh += POOL_STRIDE) {
                    for (int ow = 0; ow < CONV_OUTPUT_WIDTH - POOL_KERNEL_SIZE + 1; ow += POOL_STRIDE) {
                        float pool_val = max9(
                            conv_output_buffer[oc][oh][ow],
                            conv_output_buffer[oc][oh][ow+1],
                            conv_output_buffer[oc][oh][ow+2],
                            conv_output_buffer[oc][oh+1][ow],
                            conv_output_buffer[oc][oh+1][ow+1],
                            conv_output_buffer[oc][oh+1][ow+2],
                            conv_output_buffer[oc][oh+2][ow],
                            conv_output_buffer[oc][oh+2][ow+1],
                            conv_output_buffer[oc][oh+2][ow+2]
                        );
                        int pool_h = (h_start / STRIDE + oh) / POOL_STRIDE;
                        int pool_w = ow / POOL_STRIDE;
                        if (pool_h < POOL_OUTPUT_HEIGHT && pool_w < POOL_OUTPUT_WIDTH) {
                            int output_index = (oc+oc_start)*POOL_OUTPUT_HEIGHT*POOL_OUTPUT_WIDTH + pool_h*POOL_OUTPUT_WIDTH + pool_w;
                            if (pool_val > output[output_index]) {
                                output[output_index] = pool_val;
                            }
                        }
                    }
                }
            }
        }
    }
}

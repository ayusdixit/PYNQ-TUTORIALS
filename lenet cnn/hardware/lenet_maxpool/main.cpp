#include "maxpool.h"
#include <iostream>
#include <cmath>  // For floor

#define BATCH_SIZE 1
#define CHANNELS 6
#define INPUT_HEIGHT 24
#define INPUT_WIDTH 24
#define KERNEL_SIZE 2

#define OUTPUT_HEIGHT (INPUT_HEIGHT / KERNEL_SIZE)
#define OUTPUT_WIDTH (INPUT_WIDTH / KERNEL_SIZE)

#define INPUT_SIZE (BATCH_SIZE * CHANNELS * INPUT_HEIGHT * INPUT_WIDTH)
#define OUTPUT_SIZE (BATCH_SIZE * CHANNELS * OUTPUT_HEIGHT * OUTPUT_WIDTH)

// Function to replicate max_pool2d(x, 2)
void maxpool_2d(
    double  input[INPUT_SIZE],   // Input 1D array
	double output[OUTPUT_SIZE]  // Output 1D array
)
{
    // Interface Pragmas for hardware synthesis
#pragma HLS INTERFACE m_axi port=input depth=INPUT_SIZE offset=slave
#pragma HLS INTERFACE m_axi port=output depth=OUTPUT_SIZE offset=slave
#pragma HLS INTERFACE s_axilite port=return

    // Declare input and output buffers (reshaped to 4D)
	double input_buffer[BATCH_SIZE][CHANNELS][INPUT_HEIGHT][INPUT_WIDTH];
	double output_buffer[BATCH_SIZE][CHANNELS][OUTPUT_HEIGHT][OUTPUT_WIDTH];

    // Load 1D input into 4D input buffer
    int idx = 0;
    for (int n = 0; n < BATCH_SIZE; ++n) {
        for (int c = 0; c < CHANNELS; ++c) {
            for (int h = 0; h < INPUT_HEIGHT; ++h) {
                for (int w = 0; w < INPUT_WIDTH; ++w) {
                    input_buffer[n][c][h][w] = max[idx++];
                }
            }
        }
    }

    // Perform max pooling (2x2 kernel size, step size 2)
    for (int n = 0; n < BATCH_SIZE; ++n) {
        for (int c = 0; c < CHANNELS; ++c) {
            for (int h = 0; h < OUTPUT_HEIGHT; ++h) {
                for (int w = 0; w < OUTPUT_WIDTH; ++w) {
                    // Initialize with the top-left value in the 2x2 window
                	double max_val = input_buffer[n][c][h * 2][w * 2];

                    // Iterate over the 2x2 window
                    for (int kh = 0; kh < KERNEL_SIZE; ++kh) {
                        for (int kw = 0; kw < KERNEL_SIZE; ++kw) {
                        	double val = input_buffer[n][c][h * 2 + kh][w * 2 + kw];
                            if (val > max_val) {
                                max_val = val;
                            }
                        }
                    }

                    // Store the maximum value in the output buffer
                    output_buffer[n][c][h][w] = max_val;
                }
            }
        }
    }

    // Flatten the 4D output buffer back to 1D output array
    idx = 0;
    for (int n = 0; n < BATCH_SIZE; ++n) {
        for (int c = 0; c < CHANNELS; ++c) {
            for (int h = 0; h < OUTPUT_HEIGHT; ++h) {
                for (int w = 0; w < OUTPUT_WIDTH; ++w) {
                    output[idx++] = output_buffer[n][c][h][w];
                }
            }
        }
    }
}

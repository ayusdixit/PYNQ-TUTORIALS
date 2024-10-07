#include "maxpool.h"
#include <stdio.h>

#define BATCH_SIZE 1
#define CHANNELS 6
#define INPUT_HEIGHT 24
#define INPUT_WIDTH 24
#define OUTPUT_HEIGHT 12
#define OUTPUT_WIDTH 12

#define INPUT_SIZE (BATCH_SIZE * CHANNELS * INPUT_HEIGHT * INPUT_WIDTH)
#define OUTPUT_SIZE (BATCH_SIZE * CHANNELS * OUTPUT_HEIGHT * OUTPUT_WIDTH)

void maxpool_2d(double input[INPUT_SIZE], double output[OUTPUT_SIZE]);



int main()
{
    double local_inputs[INPUT_SIZE];
    double output[OUTPUT_SIZE];

    // Copy the predefined inputs to a local 1D array
    for (int i = 0; i < INPUT_SIZE; i++) {
    	   local_inputs[i] = (double)max[i];
        printf("Debug: local_inputs[%d] = %f\n", i, local_inputs[i]);
    }

    // Call the maxpool_2d function
    maxpool_2d(local_inputs, output);

    // Print a sample of the output
    printf("\nSample of output:\n");
    for (int i = 0; i < 30; i++) {
        printf("output[%d] = %f\n", i, output[i]);
    }

    printf("\nExecution completed\n");
    return 0;
}

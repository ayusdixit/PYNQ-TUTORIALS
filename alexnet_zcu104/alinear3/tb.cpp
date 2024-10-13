#include "dense3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hls_math.h"


void dense_layer(float inputs[4096], float weights[2 * 4096], float bias[2], float outputs[2]);


int main()
{
	float local_input[4096];
	    float local_weights[2 * 4096];  // 2 output neurons, 4096 inputs
	    float local_bias[2];            // 2 bias values
	    float final_output[2];

    // Initialize input with simple pattern
    for (int i = 0; i < 4096; i++) {
        local_input[i] = (float)input[i];
    }
     for (int i = 0; i < 8192; i++) {
        local_weights[i] = (float)dense3_weights[i];
    }
    for (int i = 0; i < 2; i++) {
        local_weights[i] = (float)dense3_bias[i];
    }

    // Print first few input values
    printf("Input (first 10 values):\n");
    for (int i = 0; i < 10; i++) {
        printf("%f ", local_input[i]);
    }
    printf("\n\n");

    // Call conv2 function
    dense_layer(local_input, local_weights, local_bias, final_output);
    // Print first few output values
    printf("Output (first 20 values):\n");
    for (int i = 0; i < 2; i++) {
    	  printf("output[%d] = %f\n", i, final_output[i]);    }
    printf("\n");

    return 0;
}

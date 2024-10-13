#include "conv1.h"
#include <stdio.h>

// Function prototype
void conv1(float input[150528], float weights[23232], float final_buffer[46656]);          //[193600]);

int main()
{
    float local_input[150528];
    float local_weights[23232];
    float final_buffer[46656];//         [193600]  ; // Initialize output to zero

    // Initialize input, weights, and bias from conv1.h
    printf("Initializing input, weights, and bias from conv1.h...\n");
    for (int i = 0; i < 150528; i++) {
        local_input[i] = (float)inp[i];
    }
    for (int i = 0; i < 23232; i++) {
        local_weights[i] = (float)conv1_weights[i];
    }


    // Print first few input values
    printf("Input (first 10 values):\n");
    for (int i = 0; i < 10; i++) {
        printf("%f ", local_input[i]);
    }
    printf("\n\n");

    // Print first few weight values
    printf("Weights (first 10 values):\n");
    for (int i = 0; i < 10; i++) {
        printf("%f ", local_weights[i]);
    }
    printf("\n\n");




    // Call conv1 function
    printf("Calling conv1 function...\n");
    conv1(local_input, local_weights, final_buffer);

    // Print first few output values
    printf("Output (first 20 values):\n");
    for (int i = 0; i < 20; i++) {
        printf("output[%d] = %f\n", i, final_buffer[i]);
    }

    // Check if all outputs are zero
    int all_zero = 1;
    float sum = 0.0f;
    float min = final_buffer[0];
    float max = final_buffer[0];
    for (int i = 0; i < 46656; i++) {
        sum += final_buffer[i];
        if (final_buffer[i] < min) min = final_buffer[i];
        if (final_buffer[i] > max) max = final_buffer[i];
        if (final_buffer[i] != 0.0f) {
            all_zero = 0;
        }
    }

    if (all_zero) {
        printf("\nWARNING: All output values are zero. This may indicate a problem.\n");
    } else {
        printf("\nSome non-zero output values found.\n");
        printf("Min value: %f\n", min);
        printf("Max value: %f\n", max);
        printf("Average value: %f\n", sum / 193600);
    }

    return 0;
}

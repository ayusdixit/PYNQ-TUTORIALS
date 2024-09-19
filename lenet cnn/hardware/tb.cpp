#include "lenet.h"
#include <stdio.h>
#include <float.h>
#include <math.h>

// Function prototype
void lenet(float input[784], float output[3456]);

int main()
{
    float local_input[784];   // Flattened 1 * 1 * 28 * 28
    float output[3456];       // Flattened 1 * 6 * 24 * 24

    // Flatten the input array
    for (int h = 0; h < 28; h++) {
        for (int w = 0; w < 28; w++) {
            local_input[h * 28 + w] = input[0][0][h][w];
        }
    }

    // Print some debug information for input
    printf("Input array (first 10 elements):\n");
    for (int i = 0; i < 10; i++) {
        printf("input[%d] = %f\n", i, local_input[i]);
    }

    // Call the lenet function
    lenet(local_input, output);

    // Print the output
    printf("\nOutput array (first 50 elements):\n");
    for (int i = 0; i < 50; i++) {
        if (isnan(output[i]) || isinf(output[i]) || fabs(output[i]) > FLT_MAX) {
            printf("Error: output[%d] = %f (Invalid value)\n", i, output[i]);
        } else {
            printf("output[%d] = %f\n", i, output[i]);
        }
    }

    // Check for any invalid values in the entire output
    int invalid_count = 0;
    for (int i = 0; i < 3456; i++) {
        if (isnan(output[i]) || isinf(output[i]) || fabs(output[i]) > FLT_MAX) {
            invalid_count++;
        }
    }

    if (invalid_count > 0) {
        printf("\nWarning: %d invalid values found in the output.\n", invalid_count);
    } else {
        printf("\nAll output values are valid.\n");
    }

    printf("Execution completed\n");
    return 0;
}

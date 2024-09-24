#include "dense1.h"
#include "dense2.h"
#include "dense3.h"
#include <stdio.h>
#include <float.h>
#include <math.h>

void dense_layer(float inputs[256], float final[10]);

int main()
{
    float local_inputs[256];
    float final[10];

    // Copy the predefined inputs to a local 1D array
    for (int i = 0; i < 256; i++) {
        local_inputs[i] = (float)inputs[i];
        printf("Debug: local_inputs[%d] = %f\n", i, local_inputs[i]);
    }

    dense_layer(local_inputs, final);

    printf("\nFinal output array (all 100 elements):\n");
    for (int i = 0; i < 10; i++) {
        if (isnan(final[i]) || isinf(final[i]) || fabs(final[i]) > FLT_MAX) {
            printf("Error: final[%d] = %f (Invalid value)\n", i, final[i]);
        } else {
            printf("final[%d] = %f\n", i, final[i]);
        }
    }

    printf("Execution completed\n");
    return 0;
}

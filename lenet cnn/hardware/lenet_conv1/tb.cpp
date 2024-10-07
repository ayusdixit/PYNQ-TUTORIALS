#include "conv1.h"
#include <stdio.h>


// Function prototype
void conv1(float input[784],  float final_buffer[864]);

int main()
{
    float local_input[784];
    float final_buffer[864] ;

    // Initialize input with simple pattern
    for (int i = 0; i < 784; i++) {
        local_input[i] = (float)input[i];
    }

    // Print first few input values
    printf("Input (first 10 values):\n");
    for (int i = 0; i < 10; i++) {
        printf("%f ", local_input[i]);
    }
    printf("\n\n");

    // Call conv2 function
    conv1(local_input, final_buffer);

    // Print first few output values
    printf("Output (first 20 values):\n");
    for (int i = 0; i < 120; i++) {
    	  printf("output[%d] = %f\n", i, final_buffer[i]);    }
    printf("\n");

    return 0;
}

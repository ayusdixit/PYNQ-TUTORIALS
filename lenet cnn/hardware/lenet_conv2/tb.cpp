#include "conv2.h"
#include <stdio.h>

#define INPUT_SIZE (1*6*12*12)
#define OUTPUT_SIZE (1*16*8*8)

// Function prototype
void conv2(float input[864],  float final_buffer[256]);

int main()
{
    float local_input[864];
    float final_buffer[256] ;

    // Initialize input with simple pattern
    for (int i = 0; i < 864; i++) {
        local_input[i] = (float)input[i];
    }

    // Print first few input values
    printf("Input (first 10 values):\n");
    for (int i = 0; i < 10; i++) {
        printf("%f ", local_input[i]);
    }
    printf("\n\n");

    // Call conv2 function
    conv2(local_input, final_buffer);

    // Print first few output values
    printf("Output (first 20 values):\n");
    for (int i = 0; i < 120; i++) {
    	  printf("output[%d] = %f\n", i, final_buffer[i]);    }
    printf("\n");

    return 0;
}

// #include "mulb.h"
//
//#include <stdio.h>
//#include <algorithm>
//#include <iostream>
//#include <random>
//#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>
//#include <string.h>
//
//void mulb(  float inputs[100]  ,float final[100]);
//
//
//
//int main()
//{
//  int i;
////  float local_inputs[100];
////   float outputs[100][10];
////   float final[100];
////   // Copy the predefined inputs to a local 1D array
////    for (int i = 0; i < 100; i++) {
////    	 local_inputs[i] = (float)inputs[i][0];
////    }
//
////   printf("Initializing input matrix...\n");
////     for (int i = 0; i < 100; i++) {
////         inputs[i][0] = static_cast<float>(i);                  // Initialize with 0 to 99
////     }
////                                                                // Print the input matrix
////     printf("Input matrix:\n");
////     for (int i = 0; i < 100; i++) {
////         std::cout << "inputs[" << i << "][0] = " << inputs[i][0] << std::endl;
////     }
//   // Print the predefined input matrix
//   // Copy the predefined inputs to a local array
//   // Print the predefined input matrix
////      printf("Predefined Input matrix:\n");
////      for (int i = 0; i < 100; i++) {
////          printf("inputs[%d][0] = %d\n", i, inputs[i][0]);
////      }
//    // Print the input array
////     printf("Input array:\n");
////     for (int i = 0; i < 100; i++) {
////         printf("inputs[%d] = %f\n", i, local_inputs[i]);
////     }
//
//    float local_inputs[100];
//    float final[100];
//
//    // Copy the predefined inputs to a local 1D array
//    for (int i = 0; i < 100; i++) {
//        local_inputs[i] = (float)inputs[i][0];
//    }
//
//    // Print the input array
//    printf("Input array:\n");
//    for (int i = 0; i < 100; i++) {
//        printf("inputs[%d] = %f\n", i, local_inputs[i]);
//    }
//
//     mulb(local_inputs, final);
//
//
////     printf("\nOutput matrix (first 5 rows):\n");
////         for (int i = 0; i < 5; i++) {                          // Print only first 5 rows for brevity
////             printf("outputs[%d] = ", i);
////             for (int j = 0; j < 10; j++) {
////                 printf("%f ", outputs[i][j]);
////             }
////             printf("\n");
////         }
////
////                                                           // Print the final output matrix (first 5 rows for brevity)
////            printf("\nFinal output matrix (after second dense layer, first 5 rows):\n");
////            for (int i = 0; i < 100; i++) {  // Print only first 5 rows
////                printf("final[%d] = %f\n", i, final[i]);
////            }
//
//            printf("\nFinal output array (all 100 elements):\n");
//              for (int i = 0; i < 100; i++) {
//                  printf("final[%d] = %f\n", i, final[i]);
//              }
//
//  printf("Success HW and SW results match\n");
//  return 0;
//}
#include "mulb.h"
#include <stdio.h>
#include <float.h>
#include <math.h>

void mulb(float inputs[100], float final[100]);

int main()
{
    float local_inputs[100];
    float final[100];

    // Copy the predefined inputs to a local 1D array
    for (int i = 0; i < 100; i++) {
        local_inputs[i] = (float)inputs[i][0];
        printf("Debug: local_inputs[%d] = %f\n", i, local_inputs[i]);
    }

    mulb(local_inputs, final);

    printf("\nFinal output array (all 100 elements):\n");
    for (int i = 0; i < 100; i++) {
        if (isnan(final[i]) || isinf(final[i]) || fabs(final[i]) > FLT_MAX) {
            printf("Error: final[%d] = %f (Invalid value)\n", i, final[i]);
        } else {
            printf("final[%d] = %f\n", i, final[i]);
        }
    }

    printf("Execution completed\n");
    return 0;
}
//
//

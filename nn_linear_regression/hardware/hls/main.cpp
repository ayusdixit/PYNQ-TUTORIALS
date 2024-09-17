#include "mulb.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

float relu(float x) {
    return x > 0 ? x : 0.0;
}

void mulb(
    float inputs[100],
    float final[100]
)
{
#pragma HLS INTERFACE m_axi port=inputs depth=MAX_SIZE offset=slave
#pragma HLS INTERFACE m_axi port=final depth=MAX_SIZE offset=slave
#pragma HLS INTERFACE s_axilite port=return

    float input_buffer[100][1];
    float output_buffer[100][10];
    float final_buffer[100][1];

    // Convert 1D input to 2D input_buffer
    for (int i = 0; i < 100; ++i) {
        input_buffer[i][0] = inputs[i];
       // printf("Debug: input_buffer[%d][0] = %f\n", i, input_buffer[i][0]);
    }

    for (int batch = 0; batch < 100; batch++) {
        for (int i = 0; i < 10; i++) {
            float value = input_buffer[batch][0] * w1[i][0] + b1[i];
            output_buffer[batch][i] = relu(value);
          //  printf("Debug: output_buffer[%d][%d] = %f\n", batch, i, output_buffer[batch][i]);
        }
    }

    for (int batch = 0; batch < 100; batch++) {
        float sum = 0.0;
        for (int i = 0; i < 10; i++) {
            sum += output_buffer[batch][i] * w2[0][i];
        }
        final_buffer[batch][0] = sum + b2[0];
       // printf("Debug: final_buffer[%d][0] = %f\n", batch, final_buffer[batch][0]);
    }

     for (int i = 0; i < 100; ++i) {
        final[i] = final_buffer[i][0];
        //printf("Debug: final[%d] = %f\n", i, final[i]);
    }
}









// #include "mulb.h"
//
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//#define MAX_SIZE 100
//
////activation function
//float  relu(float     x) {
//    return x > 0 ? x : 0.0;
//}
//
//
/////main function
//void mulb(
//      float     inputs [100]     ,  //       [1],
//    //float outputs[100][10],
// float     final[100]         //[1]
//
//)
//{
//#pragma HLS INTERFACE m_axi port=inputs depth=MAX_SIZE*MAX_SIZE offset=slave
//
////#pragma HLS INTERFACE m_axi port=outputs depth=MAX_SIZE*MAX_SIZE offset=slave
//
//#pragma HLS INTERFACE m_axi port=final depth=MAX_SIZE*MAX_SIZE offset=slave
//
//#pragma HLS INTERFACE s_axilite port=return
//
//		    int     input_buffer[100][1];
//
//		  float     output_buffer[100][10];
//
//		    float     final_buffer[100][1] ;
//
////		    for (int i = 0; i < 100; ++i) {
////		          input_buffer[i][0] = (float)((int*)inputs)[i];
////		      }
//		    // Convert 1D input to 2D input_buffer
//		    for (int i = 0; i < 100; ++i) {
//		        input_buffer[i][0] = (float)((int*)inputs)[i];
//		    }
//
////memcpy(input_buffer, inputs, 100 * 1 * sizeof(float));
////// Print input values
////  for (int i = 0; i < 100; ++i) {
////      printf("inputs[%d][0] = %f\n", i, input_buffer[i][0]);
////  }
//
//
//for (int batch = 0; batch < 100; batch++) {
//    for (int i = 0; i < 10; i++) {
//    	 float   value = input_buffer[batch][0] * w1[i][0] + b1[i];
//    	 output_buffer[batch][i] = relu(value);
//     }
//}
//
//
////memcpy(outputs, output_buffer, 100 * 10 * sizeof(float));
//for (int batch = 0; batch < 100; batch++) {
//      float sum = 0.0;
//      for (int i = 0; i < 10; i++) {
//          sum += output_buffer[batch][i] * w2[0][i];
//      }
//      final_buffer[batch][0] = sum + b2[0];
//  }
//// Convert 2D final_buffer to 1D final
// for (int i = 0; i < 100; ++i) {
//     final[i] = final_buffer[i][0];
// }
//   memcpy(final, final_buffer, 100 * 1 * sizeof(float));
//
//
//}
//
//
//
//
//
//
//
//



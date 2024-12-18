

#ifndef DNN_PARAMETERS_H
#define DNN_PARAMETERS_H

#include <stdint.h>

#define NUM_OUTPUTS 10
#define WEIGHTS_SIZE (NUM_OUTPUTS * 784)  // Example size for memory constraints

extern const float biases[NUM_OUTPUTS];
extern const float weights[WEIGHTS_SIZE];

#endif // DNN_PARAMETERS_H

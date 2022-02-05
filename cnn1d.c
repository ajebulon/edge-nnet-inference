#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    PADDING_SAME,
    PADDING_VALID
} padding;

typedef struct cnn1d_input {
    float **x;
    uint32_t channel;
    uint32_t seq_length;
} cnn1d_input_t;

typedef struct cnn1d_layer {
    float ***w;
    float *b;
    uint32_t filter;
    uint32_t kernel;
    uint32_t stride;
    padding type;
} cnn1d_layer_t;

int main(int argc, char *argv[]) {

    // Input sequence
    uint32_t channel = 1;
    uint32_t seq_length = 4;

    // Input sequence - memory allocation
    float **x = (float **)malloc(channel * sizeof(float *));
    for (int channel_idx = 0; channel_idx < channel; channel_idx++) {
        x[channel_idx] = (float *)malloc(seq_length * sizeof(float));
    }

    // Input sequence - memory initialization
    for (int channel_idx = 0; channel_idx < channel; channel_idx++) {
        for (int seq_idx = 0; seq_idx < seq_length; seq_idx++) {
            x[channel_idx][seq_idx] = channel_idx + seq_idx + 1;
        }
    }

    // Input sequence - initialized memory show
    for (int channel_idx = 0; channel_idx < channel; channel_idx++) {
        for (int seq_idx = 0; seq_idx < seq_length; seq_idx++) {
            printf("x[%d][%d]: %.2f\n", channel_idx, seq_idx, x[channel_idx][seq_idx]);
        }
    }

    // Input sequence - structure creation
    cnn1d_input_t *input = (cnn1d_input_t *)malloc(sizeof(cnn1d_input_t));
    input->channel = channel;
    input->seq_length = seq_length;
    input->x = x;

    // Layer creation
    uint32_t filter = 64;
    uint32_t kernel = 2;
    uint32_t stride = 1;
    padding type = PADDING_SAME;

    // Layer weight - memory allocation
    float ***w = (float ***)malloc(channel * sizeof(float **));
    for (int kernel_idx = 0; kernel_idx < kernel; kernel_idx++) {
        w[kernel_idx] = (float **)malloc(kernel * sizeof(float *));
        for (int channel_idx = 0; channel_idx < channel; channel_idx++) {
            w[kernel_idx][channel_idx] = (float *)malloc(filter * sizeof(float));
        }
    }

    // Layer weight - memory initialization
    for (int kernel_idx = 0; kernel_idx < kernel; kernel_idx++) {
        for (int channel_idx = 0; channel_idx < channel; channel_idx++) {
            for (int filter_idx = 0; filter_idx < filter; filter_idx++) {
                w[kernel_idx][channel_idx][filter_idx] = kernel_idx + channel_idx + filter_idx;
            }
        }
    }

    // Layer weight - initialied memory show
    for (int kernel_idx = 0; kernel_idx < kernel; kernel_idx++) {
        for (int channel_idx = 0; channel_idx < channel; channel_idx++) {
            for (int filter_idx = 0; filter_idx < filter; filter_idx++) {
                printf("w[%d][%d][%d] = %.2f\n", kernel_idx, channel_idx, filter_idx, w[kernel_idx][channel_idx][filter_idx]);
            }
        }
    }

    // Layer bias - memory allocation 
    float *b = (float *)malloc(filter * sizeof(float));
    
    // Layer bias - memory initialization
    for (int filter_idx = 0; filter_idx < filter; filter_idx++) {
        b[filter_idx] = filter_idx;
    }

    // Layer bias - initialized memory show
    for (int filter_idx = 0; filter_idx < filter; filter_idx++) {
        printf("b[%d]: %.2f\n", filter_idx, b[filter_idx]);
    }

    // Matrix multiplication
    
    

    return 0;
}
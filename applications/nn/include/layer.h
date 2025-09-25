#pragma once

#include <stdint.h>

typedef struct {
    uint64_t in_size, out_size;

    int64_t * in;
    int64_t * pre_out;
    int64_t * out;

    int64_t * biases;
    int64_t * weights;
} layer_t;

void layer_init(layer_t * layer, uint64_t in_size, uint64_t out_size, int64_t * in, int64_t * out);
void layer_free(layer_t * layer);

void layer_activate(layer_t * layer);
void layer_learn(layer_t * layer, int64_t * costs, int64_t * costs_out);

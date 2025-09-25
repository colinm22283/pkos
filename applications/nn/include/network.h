#pragma once

#include <layer.h>

typedef struct {
    uint64_t in_size;

    uint64_t layer_count;
    layer_t * layers;

    int64_t ** neurons;
} network_t;

void network_init(network_t * net, uint64_t in_size);
void network_free(network_t * net);

void network_add_layer(network_t * net, uint64_t out_size);

void network_activate(network_t * net, int64_t * input);
void network_learn(network_t * net, int64_t * correct);

int64_t network_cost(network_t * net, int64_t * input, int64_t * output);


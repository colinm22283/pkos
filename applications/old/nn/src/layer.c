#include <heap.h>
#include <fixed.h>

#include <config.h>
#include <layer.h>
#include <fixed.h>

void layer_init(layer_t * layer, uint64_t in_size, uint64_t out_size, int64_t * in, int64_t * out) {
    layer->in_size = in_size;
    layer->out_size = out_size;
    layer->in = in;
    layer->out = out;

    layer->pre_out = heap_alloc(out_size * sizeof(int64_t));
    layer->biases = heap_alloc(out_size * sizeof(int64_t));
    layer->weights = heap_alloc(in_size * out_size * sizeof(int64_t));

    for (uint64_t i = 0; i < out_size; i++) {
        layer->biases[i] = to_fixed(1) / (i % 5 + 1);
    }

    for (uint64_t i = 0; i < in_size * out_size; i++) {
        layer->weights[i] = to_fixed(1) / (i % 5 + 1);
    }
}

void layer_free(layer_t * layer) {
    heap_free(layer->pre_out);
    heap_free(layer->biases);
    heap_free(layer->weights);
}

void layer_activate(layer_t * layer) {
    for (uint64_t i = 0; i < layer->out_size; i++) {
        int64_t acc = 0;

        for (uint64_t j = 0; j < layer->in_size; j++) {
            acc += fixed_mul(layer->in[j], layer->weights[i * layer->in_size + j]);
        }

        acc += layer->biases[i];

        layer->pre_out[i] = acc;

        if (acc > 0) layer->out[i] = acc;
        else layer->out[i] = fixed_div(acc, to_fixed(10));
    }
}

void layer_learn(layer_t * layer, int64_t * costs, int64_t * costs_out) {
    for (uint64_t j = 0; j < layer->in_size; j++) {
        costs_out[j] = 0;
    }

    for (uint64_t i = 0; i < layer->out_size; i++) {
        int64_t act_deriv;
        if (layer->pre_out[i] > 0) act_deriv = to_fixed(1);
        else act_deriv = to_fixed(1) / 10;

        int64_t move_factor = fixed_mul(costs[i], act_deriv);

        int64_t * bias = &layer->biases[i];

        for (uint64_t j = 0; j < layer->in_size; j++) {
            int64_t * weight = &layer->weights[i * layer->in_size + j];

            costs_out[j] += fixed_mul(
                move_factor,
                *weight
            );

            *weight -= fixed_mul(fixed_mul(
                move_factor,
                layer->in[j]),
                learning_rate
            );
        }

        *bias -= fixed_mul(
            move_factor,
            learning_rate
        );
    }
}


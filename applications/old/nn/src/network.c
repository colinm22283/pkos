#include <heap.h>
#include <memcpy.h>

#include <network.h>
#include <fixed.h>

void network_init(network_t * net, uint64_t in_size) {
    net->in_size = in_size;

    net->layer_count = 0;
    net->layers = heap_alloc(1 * sizeof(layer_t));

    net->neurons = heap_alloc(2 * sizeof(int64_t *));
    net->neurons[0] = heap_alloc(in_size * sizeof(int64_t));
}

void network_free(network_t * net) {
    for (uint64_t i = 0; i < net->layer_count; i++) {
        layer_free(&net->layers[i]);
        heap_free(net->neurons[i]);
    }
    heap_free(net->neurons[net->layer_count]);
    
    heap_free(net->layers);
    heap_free(net->neurons);
}

void network_add_layer(network_t * net, uint64_t out_size) {
    net->layer_count++;

    net->layers = heap_realloc(net->layers, (net->layer_count + 1) * sizeof(layer_t));

    uint64_t in_size;
    if (net->layer_count == 1) in_size = net->in_size;
    else in_size = net->layers[net->layer_count - 2].out_size;

    net->neurons = heap_realloc(net->neurons, (net->layer_count + 2) * sizeof(int64_t *));
    net->neurons[net->layer_count] = heap_alloc(out_size * sizeof(int64_t));

    layer_init(
        &net->layers[net->layer_count - 1],
        in_size,
        out_size,
        net->neurons[net->layer_count - 1],
        net->neurons[net->layer_count]
    );
}

void network_activate(network_t * net, int64_t * input) {
    memcpy((char *) net->layers[0].in, (char *) input, net->in_size * sizeof(int64_t));

    for (uint64_t i = 0; i < net->layer_count; i++) {
        layer_activate(&net->layers[i]);
    }
}

void network_learn(network_t * net, int64_t * correct) {
    uint64_t out_size = net->layers[net->layer_count - 1].out_size;

    int64_t * costs = heap_alloc(out_size * sizeof(int64_t));

    for (uint64_t i = 0; i < out_size; i++) {
        costs[i] = fixed_div(
            fixed_mul(
                to_fixed(2),
                net->layers[net->layer_count - 1].out[i] - correct[i]
            ),
            to_fixed(out_size)
        );
    }

    for (uint64_t _i = 0; _i < net->layer_count; _i++) {
        uint64_t i = net->layer_count - 1 - _i;

        layer_t * layer = &net->layers[i];

        int64_t new_costs[layer->in_size];

        layer_learn(layer, costs, new_costs);

        {
            void * old_costs = costs;
            costs = heap_alloc(layer->in_size * sizeof(int64_t));
            heap_free(old_costs);
        }
        memcpy((char *) costs, (char *) new_costs, layer->in_size * sizeof(int64_t));
    }

    heap_free(costs);
}

int64_t network_cost(network_t * net, int64_t * input, int64_t * output) {
    uint64_t out_size = net->layers[net->layer_count - 1].out_size;

    int64_t cost = 0;

    network_activate(net, input);

    for (uint64_t j = 0; j < out_size; j++) {
        int64_t temp = net->layers[net->layer_count - 1].out[j] - output[j];

        cost += fixed_mul(temp, temp);
    }

    cost = fixed_div(cost, to_fixed(out_size));

    return cost;
}


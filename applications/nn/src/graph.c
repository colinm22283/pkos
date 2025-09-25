#include <graph.h>

void graph(void) {
    network_t net;
    network_init(&net, 2);

    network_add_layer(&net, 8);
    network_add_layer(&net, 1);

    print("Network ready\n");

    int64_t in[4][2] = {
        { to_fixed(0), to_fixed(0) },
        { to_fixed(0), to_fixed(1) },
        { to_fixed(1), to_fixed(0) },
        { to_fixed(1), to_fixed(1) }
    };
    int64_t out[4][1] = {
        { to_fixed(0) },
        { to_fixed(1) },
        { to_fixed(1) },
        { to_fixed(0) }
    };

    const int64_t max = to_fixed(1) / 3 * 2;
    const uint64_t width = 40;
    const uint64_t height = 24;

    int64_t costs[width];

    for (uint64_t i = 0; i < width; i++) {
        for (uint64_t j = 0; j < 40; j++) {
            network_activate(&net, in[j % 4]);
            network_learn(&net, out[j % 4]);
        }

        costs[i] = 0;
        costs[i] += network_cost(&net, in[0], out[0]);
        costs[i] += network_cost(&net, in[1], out[1]);
        costs[i] += network_cost(&net, in[2], out[2]);
        costs[i] += network_cost(&net, in[3], out[3]);
        costs[i] = fixed_div(costs[i], to_fixed(4));
    }

    int64_t div = fixed_div(max, to_fixed(height));

    for (uint64_t i = 0; i < height; i++) {
        for (uint64_t j = 0; j < width; j++) {
            if (costs[j] > fixed_mul(to_fixed(height - i - 1), div)) {
                print("#");
            }
            else {
                print(" ");
            }
        }
        print("\n");
    }

    print("Network test:\n");
    for (uint64_t i = 0; i < 4; i++) {
        network_activate(&net, in[i]);

        print("  { ");
        print_fixed(in[i][0], 4);
        print(", ");
        print_fixed(in[i][1], 4);
        print(" }: ");
        print_fixed(net.neurons[net.layer_count][0], 4);
        print(" [");
        print_fixed(out[i][0], 4);
        print("]\n");
    }

    network_free(&net);
}

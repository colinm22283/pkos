#include <hw.h>

void hw(void) {
    network_t net;
    network_init(&net, 2);

    network_add_layer(&net, 3);
    network_add_layer(&net, 2);

    net.layers[0].weights[0 * 2 * 0] = 0.1;
    net.layers[0].weights[1 * 2 * 0] = 0.3;
    net.layers[0].weights[2 * 2 * 0] = 0.4;
    net.layers[0].weights[0 * 2 * 1] = 0.2;
    net.layers[0].weights[1 * 2 * 1] = 0.2;
    net.layers[0].weights[2 * 2 * 1] = 0.1;

    net.layers[1].weights[0 * 2 * 0] = 0.3;
    net.layers[1].weights[1 * 2 * 0] = 0.1;
    net.layers[1].weights[0 * 2 * 1] = 0.5;
    net.layers[1].weights[1 * 2 * 1] = 0.6;
    net.layers[1].weights[0 * 2 * 2] = 0.2;
    net.layers[1].weights[1 * 2 * 2] = 0.7;

    print("Network ready\n");

    network_free(&net);
}

#include <stdint.h>
#include <stdbool.h>

#include <heap.h>
#include <string.h>
#include <print.h>
#include <fixed.h>

#include <network.h>
#include <config.h>

#include <graph.h>
#include <hw.h>

int main(uint64_t argc, const char ** argv) {
    if (argc != 2) return 1;

    heap_init();
    config_init();

    print("Learning rate: ");
    print_fixed(learning_rate, 10);
    print("\n");

    if (strcmp(argv[1], "graph") == 0) graph();
    else if (strcmp(argv[1], "hw") == 0) hw();

    print("Done\n");

    return 0;
}

#include <stdio.h>

#include <obj_parser.h>

int main(int argc, char ** argv) {
    if (argc != 3) {
        printf("Invalid arguments. Expected 2\n");
        return 1;
    }

    int result;

    obj_parser_t parser;

    result = op_init(&parser, argv[1]);
    if (result != 0) return result;
    result = op_read(&parser);
    if (result != 0) return result;

    printf("Section count: %lu\n", parser.sections_count);

    for (size_t i = 0; i < parser.sections_count; i++) {
        section_t * section = &parser.sections[i];

        printf("Section: %lu, %lu\n", section->base, section->size);

        for (size_t j = 0; j < section->size; j++) {
            for (size_t k = 0; k < 10; k++) {
                printf("%2x ", section->data[j]);

                j++;
            }
            printf("\n");
        }
    }

    result = op_free(&parser);
    if (result != 0) return result;

    return 0;
}
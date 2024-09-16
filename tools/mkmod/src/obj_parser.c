#include <stdlib.h>
#include <string.h>

#include <obj_parser.h>

int op_init(obj_parser_t * parser, const char * path) {
    parser->file = fopen(path, "r");
    if (parser->file == NULL) {
        printf("Unable to open file \"%s\" for reading\n", path);
        return 1;
    }

    parser->sections_count = 0;
    parser->sections = NULL;

    return 0;
}

int op_free(obj_parser_t * parser) {
    for (size_t i = 0; i < parser->sections_count; i++) free(parser->sections[i].data);

    free(parser->sections);

    fclose(parser->file);

    return 0;
}

int op_read(obj_parser_t * parser) {
    fseek(parser->file, 0, SEEK_SET);

    elf_header_t elf_header;

    if (fread(&elf_header, 1, sizeof(elf_header_t), parser->file) != sizeof(elf_header_t)) {
        printf("Unable to read ELF header\n");
        return 1;
    }

    if (strncmp("\177ELF", elf_header.magic_number, 4) != 0) {
        printf("Invalid ELF magic number");
        return 2;
    }

    parser->sections_count = elf_header.section_header_entries;
    parser->sections = malloc(parser->sections_count * sizeof(section_t));

    fseek(parser->file, (long) elf_header.section_header_table_offset, SEEK_SET);

    for (size_t i = 0; i < parser->sections_count; i++) {
        char buffer[elf_header.section_header_entry_size];
        elf_section_t * section = (elf_section_t *) &buffer;

        if (fread(buffer, 1, elf_header.section_header_entry_size, parser->file) != elf_header.section_header_entry_size) {
            printf("Unable to read section header with index %lu\n", i);
            return 3;
        }

        parser->sections[i].base = section->physical_address;
        parser->sections[i].size = section->file_segment_size;
    }

    for (size_t i = 0; i < parser->sections_count; i++) {
        section_t * section = &parser->sections[i];

        section->data = malloc(section->size);

        fseek(parser->file, (long) section->base, SEEK_SET);
        if (fread(section->data, 1, section->size, parser->file) != section->size) {
            printf("Error while reading section with index %lu\n", i);
            return 4;
        }
    }

    return 0;
}
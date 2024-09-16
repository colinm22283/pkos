#pragma once

#include <stdio.h>
#include <stdint.h>

typedef struct {
    size_t base;
    size_t size;
    char * data;
} section_t;

typedef struct {
    FILE * file;

    size_t sections_count;
    section_t * sections;
} obj_parser_t;

typedef struct __attribute__((packed)) {
    char magic_number[4];
    uint8_t register_width;
    uint8_t endianness;
    uint8_t elf_header_version;
    uint8_t os_abi;
    uint8_t _padding0[8];
    uint16_t type;
    uint16_t instruction_set;
    uint32_t elf_version;
    uint64_t entry_point;
    uint64_t program_header_table_offset;
    uint64_t section_header_table_offset;
    uint32_t flags;
    uint16_t elf_header_size;
    uint16_t program_header_entry_size;
    uint16_t program_header_entries;
    uint16_t section_header_entry_size;
    uint16_t section_header_entries;
    uint16_t section_index;
} elf_header_t;

typedef struct __attribute__((packed)) {
    uint32_t segment_type;
    uint32_t flags;
    uint64_t data_offset;
    uint64_t virtual_address;
    uint64_t physical_address;
    uint64_t file_segment_size;
    uint64_t memory_segment_size;
    uint64_t segment_alignment;
} elf_section_t;

int op_init(obj_parser_t * parser, const char * path);
int op_free(obj_parser_t * parser);

int op_read(obj_parser_t * parser);
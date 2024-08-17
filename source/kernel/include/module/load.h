#pragma once

#include <module/info_table.h>

#include <filesystem/filesystem.h>

module_info_table_t * module_load(directory_t dir, const char * path);
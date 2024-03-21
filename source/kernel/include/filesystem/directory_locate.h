#pragma once

#include <stdbool.h>

#include <filesystem/filesystem.h>

bool filesystem_directory_locate(filesystem_directory_page_t * directory, const char * name, void * result_page);
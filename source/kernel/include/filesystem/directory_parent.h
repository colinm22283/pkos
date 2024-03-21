#pragma once

#include <stdbool.h>

#include <filesystem/filesystem.h>

bool filesystem_directory_parent(filesystem_directory_page_t * directory, filesystem_directory_page_t * result);
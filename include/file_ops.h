#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#define S_777 S_IRWXU | S_IRWXG | S_IRWXO

size_t get_file_size(const char* filename);

#endif
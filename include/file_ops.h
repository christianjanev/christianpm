#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <linux/limits.h> // PATH_MAX

#define S_777 S_IRWXU | S_IRWXG | S_IRWXO

int is_path_dir(const char* filename);
int walk_directory(const char* directory_path, int (*fn)(char*));

#endif
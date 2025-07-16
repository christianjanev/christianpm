#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <stdlib.h>

int create_archive(const char* input_filenames[], const char* output_filename, int file_count);
int read_archive(const char* archive_to_read);

#endif

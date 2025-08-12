#include "../include/archive.h"
#include "../include/enums.h"
#include "../include/file_ops.h"

int create_archive(const char* input_filenames[], const char* output_filename, int file_count)
{
	struct archive* new_archive = archive_write_new();
	if (new_archive != NULL) {
		archive_write_open_filename(new_archive, output_filename);

		archive_write_set_format_gnutar(new_archive);
		
		for (int i=0; i<file_count; i++) {
			struct stat file_stat;
			stat(input_filenames[i], &file_stat);
			short is_dir = S_ISDIR(file_stat.st_mode);

			FILE* text = fopen(input_filenames[i], "rb");

			if (text != NULL) {
				long file_size = get_file_size(input_filenames[i]);
				unsigned char* text_data = (unsigned char*)malloc(file_size);
				fread(text_data, 1, file_size, text);
				fclose(text);

				struct archive_entry* new_entry = archive_entry_new();
				archive_entry_set_pathname(new_entry, input_filenames[i]);
				if (is_dir) archive_entry_set_filetype(new_entry, AE_IFDIR);
				else archive_entry_set_filetype(new_entry, AE_IFREG);

				struct stat new_stat;
				stat(input_filenames[i], &new_stat);
				archive_entry_copy_stat(new_entry, &new_stat);

				struct archive* parchive_read = archive_read_disk_new();
				archive_read_disk_descend(parchive_read);

				int header_written = archive_write_header(new_archive, new_entry);

				if (header_written == ARCHIVE_OK) {
					archive_write_data(new_archive, text_data, file_size);
				} else {
					printf("Error writing header. Error: %s\n", archive_error_string(new_archive));
					return ARCHIVE_ENTRY_WRITE_ERROR;
				}

				free(text_data);
			} else {
				printf("Error opening file: %s\n", input_filenames[i]);
				return FILE_OPEN_ERROR;
			}
		}
		archive_write_free(new_archive);
	} else {
		printf("Error creating archive.\n");
		return ARCHIVE_CREATION_ERROR;
	}

	return ARCHIVE_SUCCESS;
}

int read_archive(const char* archive_to_read)
{
    struct archive* parchive_read = archive_read_new();

    if (!parchive_read) return ARCHIVE_CREATION_ERROR;

	if (archive_read_support_format_gnutar(parchive_read) == ARCHIVE_FATAL) return ARCHIVE_FORMAT_ERROR;

	if (archive_read_open_filename(parchive_read, archive_to_read, get_file_size(archive_to_read)) == ARCHIVE_FATAL) return ARCHIVE_OPEN_ERROR;

	struct archive_entry *pentry;

	while (archive_read_next_header(parchive_read, &pentry) != ARCHIVE_EOF) {
		int64_t entry_size = archive_entry_size(pentry);
		printf("Size: %ld\n", entry_size);
		unsigned char* buffer = (unsigned char*)malloc(entry_size);
		archive_read_data(parchive_read, buffer, entry_size);
		printf("Data: %s\n", buffer);
		free(buffer);
	}

	archive_read_close(parchive_read);

    return ARCHIVE_SUCCESS;
}

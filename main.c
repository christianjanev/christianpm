#include <stdio.h>

#include "include/archive.h"

#define SIZE_OF_ARRAY(a) sizeof(a)/sizeof(a[0])

int length_of_string_array(const char* array[]);

int main()
{
	const char* files[5] = {"to_archive/", "to_archive/test.txt", "to_archive/test2.txt", "to_archive/test3.txt", "to_archive/test4.txt"};
	create_archive(files, "package.cpm", SIZE_OF_ARRAY(files));
	printf("%d\n", read_archive("hello"));
	return 0;
}

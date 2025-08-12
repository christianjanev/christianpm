#include <stdio.h>

#include "include/archive.h"

#define SIZE_OF_ARRAY(a) sizeof(a)/sizeof(a[0])

int main(const int argc, char* argv[])
{
	// const char* files[5] = {"to_archive/", "to_archive/test.txt", "to_archive/test2.txt", "to_archive/test3.txt", "to_archive/test4.txt"};
	const char* files[] = {"test.txt"};
	create_archive(files, "package.cpm", SIZE_OF_ARRAY(files));
	printf("%d\n", read_archive("package.cpm"));
	return 0;
}

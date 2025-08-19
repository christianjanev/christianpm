#include "../include/file_ops.h"

int is_path_dir(const char* filename)
{
    struct stat file_stat;
    stat(filename, &file_stat);
    return S_ISDIR(file_stat.st_mode);
}

int walk_directory(const char* directory_path, int (*fn)(char*))
{
    DIR* directory = opendir(directory_path);
    struct dirent* file;
    while ((file = readdir(directory)) != NULL)
    {
        if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
        {
            char* fullpath = (char*)malloc(PATH_MAX);
            strcpy(fullpath, directory_path);
            strcat(fullpath, file->d_name);
            if (is_path_dir(fullpath))
            {
                strcat(fullpath, "/");
                walk_directory(fullpath, fn);
            }
            fn(fullpath);
        }
    }
    return 0;
}
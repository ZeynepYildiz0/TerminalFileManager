#ifndef DIRECTORY_OPS_H
#define DIRECTORY_OPS_H

void list_directory(const char *path);
void create_file_or_directory(const char *name);
void remove_file(const char *path);
void search_files(const char *directory, const char *name);

#endif // DIRECTORY_OPS_H


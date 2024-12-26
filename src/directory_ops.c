#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "../include/logger.h"
#include "../include/directory_ops.h"

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Failed to open directory");
        log_operation("List Directory", path, "Failed");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];

    while ((entry = readdir(dir)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == -1) {
            perror("Failed to get file stats");
            continue;
        }

        printf("%-20s %10ld bytes ", entry->d_name, file_stat.st_size);

        if (S_ISREG(file_stat.st_mode)) {
            printf("[File]");
        } else if (S_ISDIR(file_stat.st_mode)) {
            printf("[Directory]");
        } else {
            printf("[Other]");
        }

        printf("\n");
    }

    closedir(dir);
    log_operation("List Directory", path, "Success");
}

void remove_file(const char *path) {
    struct stat path_stat;

     if (stat(path, &path_stat) == -1) {
        perror("Failed to get file information");
        log_operation("Remove", path, "Failed");
        return;
    }

    if (S_ISDIR(path_stat.st_mode)) {
         DIR *dir = opendir(path);
        if (!dir) {
            perror("Failed to open directory");
            log_operation("Remove", path, "Failed");
            return;
        }

        struct dirent *entry;
        int is_empty = 1;

         while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                is_empty = 0;
                break;
            }
        }

        closedir(dir);

        if (!is_empty) {
            fprintf(stderr, "Error: Directory is not empty: %s\n", path);
            log_operation("Remove", path, "Failed - Directory not empty");
            return;
        }

         if (rmdir(path) == 0) {
            printf("Directory removed successfully: %s\n", path);
            log_operation("Remove", path, "Success");
        } else {
            perror("Failed to remove directory");
            log_operation("Remove", path, "Failed");
        }
    } else {
         if (unlink(path) == 0) {
            printf("File removed successfully: %s\n", path);
            log_operation("Remove", path, "Success");
        } else {
            perror("Failed to remove file");
            log_operation("Remove", path, "Failed");
        }
    }
}

void create_file_or_directory(const char *name) {
    if (mkdir(name, 0755) == 0) {
        printf("Directory created: %s\n", name);
        log_operation("Create Directory", name, "Success");
    } else if (creat(name, 0644) != -1) {
        printf("File created: %s\n", name);
        log_operation("Create File", name, "Success");
    } else {
        perror("Failed to create file/directory");
        log_operation("Create File/Directory", name, "Failed");
    }
}

void search_files(const char *directory, const char *name) {
    DIR *dir = opendir(directory);
    if (!dir) {
        perror("Failed to open directory");
        log_operation("Search Files", directory, "Failed");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, name)) {
            printf("Found: %s/%s\n", directory, entry->d_name);
        }
    }

    closedir(dir);
    log_operation("Search Files", directory, "Success");
}




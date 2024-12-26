#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../include/file_operations.h"
#include "../include/logger.h"

void copy_file(const char *src, const char *dest) {
struct stat dest_stat;
    char dest_path[1024];

    if (stat(dest, &dest_stat) == 0 && S_ISDIR(dest_stat.st_mode)) {
        const char *filename = strrchr(src, '/');
        if (filename) {
            snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, filename + 1);
        } else {
            snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, src);
        }
    } else {
        const char *error_msg = "Error: Destination must be a directory\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg)); 
        log_operation("Copy File", dest, "Failed - Not a directory");
        return;
    }

    int src_fd = open(src, O_RDONLY);
    if (src_fd == -1) {
        perror("Failed to open source file");
        log_operation("Copy File", src, "Failed");
        return;
    }

    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Failed to open destination file");
        close(src_fd);
        log_operation("Copy File", dest_path, "Failed");
        return;
    }

    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("Failed to write to destination file");
            log_operation("Copy File", dest_path, "Failed");
            close(src_fd);
            close(dest_fd);
            return;
        }
    }

    close(src_fd);
    close(dest_fd);

    if (bytes_read == -1) {
        perror("Failed to read source file");
        log_operation("Copy File", src, "Failed");
        return;
    }

    log_operation("Copy File", dest_path, "Success");
    printf("File copied successfully to: %s\n", dest_path);
}
void view_file_content(const char *path) {
    int fd = open(path, O_RDONLY); 
   if (fd == -1) {
        perror("Failed to open file");
        log_operation("View File Content", path, "Failed");
        return;
    }

    char buffer[256];
    ssize_t bytes_read;

    
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
   	if (write(STDOUT_FILENO, buffer, bytes_read) == -1) {
            perror("Failed to write to stdout");
            log_operation("View File Content", path, "Failed");
            close(fd);
            return;
        }
    }

    if (bytes_read == -1) {
        perror("Failed to read file");
        log_operation("View File Content", path, "Failed");
    } else {
    log_operation("View File Content", path, "Success");
}

    close(fd);

}


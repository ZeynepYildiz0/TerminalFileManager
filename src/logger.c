#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "../include/logger.h"

void log_operation(const char *operation, const char *path, const char *result) {
    int log_fd = open("operations.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd == -1) {
        perror("Failed to open log file");
        return;
    }

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';

    char log_entry[512];
    snprintf(log_entry, sizeof(log_entry), "[%s] Operation: %s, Path: %s, Result: %s\n",
             time_str, operation, path, result);

    if (write(log_fd, log_entry, strlen(log_entry)) == -1) {
        perror("Failed to write to log file");
    }

    close(log_fd);
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../include/logger.h"
#include "../include/permissions.h"

void change_permissions(const char *path) {
char input[10];
    int mode;
    printf("Enter new permissions in octal (e.g., 0644): ");
    scanf("%s", input);


    for (int i = 0; i < strlen(input); i++) {
        if (input[i] < '0' || input[i] > '7') {
            printf("Error: Invalid octal value. Please enter a valid octal permission (e.g., 0644).\n");
            log_operation("Change Permissions", path, "Failed - Invalid Octal Input");
            return;
        }
    }

    mode = strtol(input, NULL, 8);

    if (chmod(path, mode) == -1) {
        perror("Failed to change permissions");
        log_operation("Change Permissions", path, "Failed");
        return;
    }

    printf("Permissions changed successfully for: %s\n", path);
    log_operation("Change Permissions", path, "Success");
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_operations.h"
#include "../include/directory_ops.h"
#include "../include/permissions.h"
#include "../include/logger.h"

void print_help() {
    printf("\nTerminal Based File Manager\n");
    printf("1. List Directory (slist): Usage - slist <directory_path>\n");
    printf("2. Copy File (scopy): Usage - scopy <source_file> <destination>\n");
    printf("3. Remove File (sremove): Usage - sremove <file_or_directory_path>\n");
    printf("4. Create File/Directory (screate): Usage - screate <name>\n");
    printf("5. View File Content (sview): Usage - sview <file_path>\n");
    printf("6. Search Files (ssearch): Usage - ssearch <directory> <name_to_search>\n");
    printf("7. Change Permissions (schmod): Usage - schmod <file_or_directory_path>\n");
    printf("8. Exit\n");
    printf("To execute commands, use: ./bin/file_manager <command> [arguments]\n\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    }

    if (strcmp(argv[1], "slist") == 0) {
        if (argc < 3) {
            printf("Usage: %s slist <directory>\n", argv[0]);
            return 1;
        }
        list_directory(argv[2]);
    } else if (strcmp(argv[1], "scopy") == 0) {
        if (argc < 4) {
            printf("Usage: %s scopy <source> <destination>\n", argv[0]);
            return 1;
        }
        copy_file(argv[2], argv[3]);
    } else if (strcmp(argv[1], "sremove") == 0) {
        if (argc < 3) {
            printf("Usage: %s sremove <file/folder>\n", argv[0]);
            return 1;
        }
        remove_file(argv[2]);
    } else if (strcmp(argv[1], "screate") == 0) {
        if (argc < 3) {
            printf("Usage: %s screate <file/folder name>\n", argv[0]);
            return 1;
        }
        create_file_or_directory(argv[2]);
    } else if (strcmp(argv[1], "sview") == 0) {
        if (argc < 3) {
            printf("Usage: %s sview <file path>\n", argv[0]);
            return 1;
        }
        view_file_content(argv[2]);
    } else if (strcmp(argv[1], "ssearch") == 0) {
        if (argc < 4) {
            printf("Usage: %s ssearch <directory> <name>\n", argv[0]);
            return 1;
        }
        search_files(argv[2], argv[3]);
    } else if (strcmp(argv[1], "schmod") == 0) {
        if (argc < 3) {
            printf("Usage: %s schmod <file/folder path>\n", argv[0]);
            return 1;
        }
        change_permissions(argv[2]);
    } else {
        printf("Unknown command: %s\n", argv[1]);
        print_help();
    }

    return 0;
}


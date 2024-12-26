CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c src/file_operations.c src/directory_ops.c src/permissions.c src/logger.c
BIN = bin/file_manager

all:
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm -rf bin
	rm -f operations.log

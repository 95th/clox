#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"
#include <stdio.h>

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stack_top;
} VM;

void initVM();
void freeVM();

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

static void repl() {
    char line[2048];
    for (;;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            print("\n");
            break;
        }

        interpret(line);
    }
}

static char* read_file(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s.\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read %s.\n", path);
        exit(74);
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read < file_size) {
        fprintf(stderr, "Could not read file %s.\n", path);
        exit(74);
    }

    buffer[bytes_read] = '\0';
    fclose(file);
    return buffer;
}

static void run_file(const char* path) {
    char* source = read_file(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR) {
        exit(65);
    }

    if (result == INTERPRET_RUNTIME_ERROR) {
        exit(70);
    }
}

#endif
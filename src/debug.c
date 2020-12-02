#include "debug.h"

#include <stdio.h>

void disassemble_chunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassemble_instr(chunk, offset);
    }
}

int simple_instr(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassemble_instr(Chunk* chunk, int offset) {
    printf("%04d ", offset);

    uint8_t instr = chunk->code[offset];
    switch (instr) {
        case OP_RETURN:
            return simple_instr("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instr);
            return offset + 1;
    }
}
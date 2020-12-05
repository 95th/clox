#include "debug.h"
#include "value.h"
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

int constant_instr(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    print_value(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

int disassemble_instr(Chunk* chunk, int offset) {
    printf("%04d ", offset);

    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("   | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }

    uint8_t instr = chunk->code[offset];
    switch (instr) {
    case OP_CONSTANT:
        return constant_instr("OP_CONSTANT", chunk, offset);
    case OP_NOT:
        return simple_instr("OP_NOT", offset);
    case OP_NEGATE:
        return simple_instr("OP_NEGATE", offset);
    case OP_ADD:
        return simple_instr("OP_ADD", offset);
    case OP_SUBTRACT:
        return simple_instr("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
        return simple_instr("OP_MULTIPLY", offset);
    case OP_DIVIDE:
        return simple_instr("OP_DIVIDE", offset);
    case OP_RETURN:
        return simple_instr("OP_RETURN", offset);
    case OP_TRUE:
        return simple_instr("OP_TRUE", offset);
    case OP_FALSE:
        return simple_instr("OP_FALSE", offset);
    case OP_NIL:
        return simple_instr("OP_NIL", offset);
    default:
        printf("Unknown opcode %d\n", instr);
        return offset + 1;
    }
}
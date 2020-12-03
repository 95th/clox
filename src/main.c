#include "chunk.h"
#include "common.h"
#include "vm.h"

int main(int argc, const char** argv) {
    initVM();

    Chunk chunk;
    init_chunk(&chunk);

    int constant = add_constant(&chunk, 1.2);
    write_chunk(&chunk, OP_CONSTANT, 123);
    write_chunk(&chunk, constant, 123);
    write_chunk(&chunk, OP_NEGATE, 123);
    int constant2 = add_constant(&chunk, 2.3);
    write_chunk(&chunk, OP_CONSTANT, 123);
    write_chunk(&chunk, constant2, 123);
    write_chunk(&chunk, OP_ADD, 123);
    write_chunk(&chunk, OP_RETURN, 123);

    interpret(&chunk);

    freeVM();
    free_chunk(&chunk);
    return 0;
}
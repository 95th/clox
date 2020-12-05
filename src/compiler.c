#include "compiler.h"
#include "common.h"
#include "scanner.h"
#include <stdio.h>

bool compile(const char* source, Chunk* chunk) {
    init_scanner(source);

    advance();
    expression();
    consume(TOKEN_EOF, "Expected end of expression");
}
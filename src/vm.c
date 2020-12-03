#include "vm.h"
#include "common.h"
#include "debug.h"
#include <stdio.h>

VM vm;

static void reset_stack() { vm.stack_top = vm.stack; }

void initVM() { reset_stack(); }
void freeVM() {}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;) {

#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value* slot = vm.stack; slot < vm.stack_top; slot++) {
            printf("[ ");
            print_value(*slot);
            printf(" ]");
        }
        printf("\n");
        disassemble_instr(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instr = READ_BYTE();
        switch (instr) {
        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            push(constant);
            break;
        }
        case OP_NEGATE: {
            push(-pop());
            break;
        }
        case OP_RETURN:
            return INTERPRET_OK;
        }
    }

#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}

void push(Value value) {
    *vm.stack_top = value;
    vm.stack_top++;
}

Value pop() {
    vm.stack_top--;
    return *vm.stack_top;
}
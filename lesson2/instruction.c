#include <stdlib.h>
#include <stdio.h>
#include "instruction.h"

int encode(struct instr_t instr) {
    int encoded;
    switch (instr.opcode){
        case MOVI:
            encoded = (instr.operand.imm & 0x7F);
            break;
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            encoded = (instr.opcode << 4) | (instr.operand.regs.rx << 2) | (instr.operand.regs.rs);
            break;
        case IN:
        case OUT:
            encoded = (instr.opcode << 2) | instr.operand.reg;
            break;
        default:
            fprintf(stderr, "Unknown opcode");
            abort();
        }
    return encoded;
}
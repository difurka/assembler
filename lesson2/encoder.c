#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction.h"

static int parse_movi() {
    char buf[16];
    int imm, res;
    struct instr_t instr;
    res = scanf("%15s", buf);
    if (res != 1 || buf[0] !='D') {
        fprintf(stderr, "D register expected in MOVI");
        abort();
    }
    res = scanf("%x", &imm);
    if (res != 1 || imm > (1<<7)) {
        fprintf(stderr, "Expected imm in MOVI");
        abort();
    }
    instr.opcode = MOVI;
    instr.operand.imm = imm;
    return encode(instr);
}


static enum reg_t parse_reg(const char reg) {
    switch (reg)
    {
    case 'A': return A;
    case 'B': return B;
    case 'C': return C;
    case 'D': return D;
    default:
        fprintf(stderr, "unknown reg<%c>", reg);
    }
}

static int parse_io(enum opcode_t op) {
    char buf[16];
    int res;
    struct instr_t instr;
    res = scanf("%15s", buf);
    if (res != 1) {
        fprintf(stderr, "register expected in IO");
        abort();
    }

    instr.opcode = op;
    instr.operand.reg = parse_reg(buf[0]);
    return encode(instr);
}

static int parse_arithm(enum opcode_t op) {
    char buf[16];
    int res;
    struct instr_t instr;
    enum reg_t rx, rs;
    res = scanf("%15s", buf);
    if (res != 1) {
        fprintf(stderr, "register expected in ARITHM");
        abort();
    }
    rx = parse_reg(buf[0]);

    res = scanf("%15s", buf);
    if (res != 1) {
        fprintf(stderr, "register expected in ARITHM");
        abort();
    }
    rs = parse_reg(buf[0]);

    instr.opcode = op;
    instr.operand.regs.rs=rs;
    instr.operand.regs.rx=rx;
    return encode(instr);
}

int main() {
    char mnemonic[16] = {0};
    while (scanf("%15s", mnemonic) == 1) {
        int encoded;
        if (strcmp(mnemonic, "MOVI") == 0) {
            encoded = parse_movi();
        } else if (strcmp(mnemonic, "ADD") == 0) {
            encoded = parse_arithm(ADD);
        } else if (strcmp(mnemonic, "SUB") == 0) {
            encoded = parse_arithm(SUB);
        } else if (strcmp(mnemonic, "MUL") == 0) {
            encoded = parse_arithm(MUL);
        } else if (strcmp(mnemonic, "DIV") == 0) {
            encoded = parse_arithm(DIV);
        } else if (strcmp(mnemonic, "IN") == 0) {
            encoded = parse_io(IN);
        } else if (strcmp(mnemonic, "OUT") == 0) {
            encoded = parse_io(OUT);
        } 
        else {
            fprintf(stderr, "unknown mnemonic: <%s>\n", mnemonic);
            abort();
        }
        printf("0x%X ", encoded);
        fflush(stdout);
    }
    printf("\n");
}
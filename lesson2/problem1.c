#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum reg_t {A=0, B=1, C = 2, D=3};
enum opcode_t {MOVI = 0, ADD=8, SUB=9, MUL=10, DIV=11, IN=0x30, OUT=0x31};


union operands_t {
    struct  {
        enum reg_t rx, rs;
    } regs;
    
    enum reg_t reg;
    int imm;

};

struct instr_t {
    union operands_t operand;
    enum opcode_t opcode;
};

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
            printf("ERROR");
            fflush(stdout);
            exit(0);
        }
    return encoded;
}

static int parse_movi() {
    // char buf[16];
    int imm, res;
    struct instr_t instr;
    res = scanf("%d", &imm);
    if (res != 1 || imm > (1<<7)) {
        printf("ERROR");
        fflush(stdout);
        exit(0);
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
        printf("ERROR");
        fflush(stdout);
        exit(0);
    }
}

static int parse_io(enum opcode_t op) {
    char buf[16];
    int res;
    struct instr_t instr;
    res = scanf("%15s", buf);
    if (res != 1) {
        printf("ERROR");
        fflush(stdout);
        exit(0);

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
        printf("ERROR");
        fflush(stdout);
        exit(0);
    
    }
    rx = parse_reg(buf[0]);

    res = scanf("%15s", buf);
    if (res != 1) {
        printf("ERROR");
        fflush(stdout);
        exit(0);
    
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
            printf("ERROR");
            fflush(stdout);
            return 0;
        }
        printf("0x%x ", encoded);
        fflush(stdout);
    }
    printf("\n");
}



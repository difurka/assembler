#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decode.h"
#include "instruction.h"

static char  parse_reg(const enum reg_t reg) {
    switch (reg)
    {
        case A: return 'A';
        case B: return 'B';
        case C: return 'C';
        case D: return 'D';
        default:
            fprintf(stderr, "unknown symbol<%c>", reg);
    }
}

void decode_movi(int value, char* decode) {
    char* oper = "MOVI ";
    strcpy(decode, oper);

    char int_to_str[16];
    sprintf(int_to_str, "%d", value & 127);
    strcat(decode, int_to_str);
}

void decode_alg(int value, char* decode) {
    char rx = parse_reg((value>>2)&3);
    char rs = parse_reg(value&3);
    char* oper;
    switch (value >>4) {
        case 8:
            oper = "ADD ";
            break;
        case 9:
            oper = "SUB ";
            break;
        case 10:
            oper = "MUL ";
            break;
        case 11:
            oper = "DIV ";
            break;
    }
    strcpy(decode, oper);
    decode[4] = rx;
    decode[5] = ',';
    decode[6] = ' ';
    decode[7] = rs;
    decode[8] = '\0';
}

void decode_io(int value, char* decode) {
    char rs = parse_reg(value&3);
    char* oper;
    switch (value >>2) {
        case 48:
            oper = "IN ";
            strcpy(decode, oper);
            decode[3] = parse_reg(value&3);
            decode[4] = '\0';
            break;
        case 49:
            oper = "OUT ";
            strcpy(decode, oper);
            decode[4] = parse_reg(value&3);
            decode[5] = '\0';
            break;
    }
}

void decode(int value) {
        char decode[16];
        if (value>>7 == 0) {
            decode_movi(value, decode);
        } else if ((value >>4) >=8 && (value >>4) <=11) {
            decode_alg(value, decode);
        } else if ((value >>2) == 48 || (value >>2) == 49) {
            decode_io(value, decode);
        } else {
            strcpy(decode,"ERROR");
        }
        printf("%s\n", decode);
}

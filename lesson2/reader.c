#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "instruction.h"

#include "decode.h"

static int AA = 0,BB=0,CC=0,DD = 0;

enum reg_t {A=0, B=1, C = 2, D=3};


int get_reg_int(const enum reg_t reg) {
    switch (reg)
    {
        case A: return AA ;
        case B: return BB ;
        case C: return CC ;
        case D: return DD ;
        default:
            fprintf(stderr, "unknown symbol<%c>", reg);
    }
    return 0;
}


int set_reg_int(const enum reg_t reg, int val) {
    switch (reg)
    {
        case A: AA = val; return 0 ;
        case B: BB = val; return 0 ;
        case C: CC = val; return 0 ;
        case D: DD = val; return 0 ;
        default:
            fprintf(stderr, "unknown symbol<%c>", reg);
    }
    return 0;
}


void do_movi(int value) {
    set_reg_int(3,value & 127);
}

void do_alg(int value) {
    int rx = get_reg_int((value>>2)&3);
    int rs = get_reg_int((value)&3);
    switch (value >>4) {
        case 8:
            rx+=rs;
            break;
        case 9:
            rx-=rs + 256;
            break;
        case 10:
            rx*=rs;
            break;
        case 11:
            rx/=rs;
            break;
    }
    set_reg_int((value>>2)&3, rx &255);
}

void do_io(int value) {
    int val;
    switch (value >>2) {
        case 48:
            scanf("%d", &val);
            set_reg_int(value&3,val);
            break;
        case 49:
            printf("%d\n", get_reg_int((value)&3));
            break;
    }
}

int main() {
    int value;
    int com[1000];
    int len = 0;
    while (scanf("%X", &value) == 1) {
         if (value == 0xff) {
            break;
        } else {
            com[len++] = value;
        }
        fflush(stdout);
    }

    for (int i= 0; i < len; ++i) {
        int value = com[i];
        // decode(value);
        if (value>>7 == 0) {
            do_movi(value);
        } else if ((value >>4) >=8 && (value >>4) <=11) {
            do_alg(value);
        } else if ((value >>2) == 48 || (value >>2) == 49) {
            do_io(value);
        } else {
            printf("ERROR\n");
            break;
        }
        fflush(stdout);
    }
}


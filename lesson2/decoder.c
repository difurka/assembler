#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char* in_bin(int dec) {
    int num_elements = 8;
    int num_bits = sizeof(int) * num_elements;
    char* res = malloc(num_bits + 1);
    
    for (int i = 8; i >= 0; i--) {
        res[8 - 1 - i] = ((dec >> i) & 1) + '0';
    }
    res[8] = '\0';
    return res;
}

int main() {
    char mnemonic[16] = {0};
    int value;
    while (scanf("%X", &value) == 1) {
        // if (strlen(mnemonic) == 4 || mnemonic[0] == '0' || mnemonic[1]=='x')
        printf("%s\n", in_bin(value));
        // fflush(stdout);
        // strncpy(char* destination, const char* source, size_t num)
    }
    printf("\n");
}

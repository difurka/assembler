#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction.h"

static char  parse_reg(const enum reg_t reg) {
    switch (reg)
    {
    case 'A': return 'A';
    case 'B': return 'B';
    case 'C': return 'C';
    case 'D': return 'D';
    default:
        fprintf(stderr, "unknown symbol<%c>", reg);
    }
}


int main() {
    char mnemonic[16] = {0};

    while (scanf("%15s", mnemonic) == 1) {
        if (strlen(mnemonic) == 4 || mnemonic[0] == '0' || mnemonic[1]=='x')
        printf("%15s\n", substr(mnemonic,2));
        // fflush(stdout);
    }
    printf("\n");
}

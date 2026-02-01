#include <stdio.h>
#include <math.h>

unsigned long long f(unsigned int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;

    unsigned long long a = 0, b = 1;
    for (unsigned int i = 2; i <=x; ++i) {
        unsigned long long c = a;
        a = b;
        b+=c;
    }
    return b;
}

int main() {
    unsigned int x;
    unsigned int m;
    scanf("%u%u", &x, &m);
    unsigned long long res = f(x)%m;
    printf("%llx", res);
}
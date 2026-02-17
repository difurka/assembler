int foo(int* a0, int a1, int a2) {
    int* t3 = a0+4*a1;
    int t1 = *t3;
    int* a7 = a0;
    if (a1>=a2) goto L5;
    int* a4 = a0+(a2<<2);
    int a3 = a2;
    int res;

    L4:
    int a6 = *a4;
    int* a5 = a7+4*a2;
    --a3;
    if (a6 <= t1) {
        a4-=4;
        if (a1<a3) goto L4;
        res = a2;
        a2 *=4;
        int temp_2 = *t3;
        a7 = a7+a2;
        int temp_1 = *a7;
        *a7 = temp_2;
        *t3 = temp_1; 
    };
    int temp = *a5;
    *a5=a6;
    --a2;
    *a4 = temp;


    L5:
    res = a2;
    a2 = a2<<2;
    a7 = a7+a2;
    int temp_2 = *a7;
    *a7 = t1;
    *t3 = temp_2;
    return res;
}




int mai() {
    int a0[7] = {0};
    foo(a0, 2,3);
}
// int foo(int* a0, int a1, int a2) {
//     // a5 = a1 << 32;
//     // t3 = a5 >> 30;
//     int* t3 = a0+((a1 << 32) >> 30);
//     int t1 = *t3;
//     int* a7 = a0;
//     if (a1>=a2) goto L5;
//     int* a4 = a0+(a2<<2);
//     int a3 = a2;

//     L4:
//     int a6 = *a4;
//     int* a5 = a7+(a2<<2);
//     --a3;
//     if (a6 <= t1) goto L3;
//     a0 = *a5;
//     *a5=a6;
//     --a2;
//     *a4 = a2;

//     L3:
//     a4-=4;
//     if (a1<a3) goto L4;
//     a0 = a2;
//     a2 = a2 <<2;
//     t1 = *t3;
//     a7 = a7+a2;
//     a5 = *a7;
//     *a7 = t1;
//     *t3 = a5;
//     break;

//     L5:
//     a0 = a2;
//     a2 = a2<<2;
//     a7 = a7+a2;
//     a5 = *a7;
//     *a7 = t1;
//     *t3 = a5;
//     break;
// }



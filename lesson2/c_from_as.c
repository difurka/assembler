int foo(int* a0, int a1, int a2) {
    int* t3= a0 + 4*a1;
    int t1 = *t3;
    int* a7 = a0;
    int a3;
    if (a1 < a2) {
        int* a4 = a0 +4*a2;
        a3 = a2;

        do {
            int a6 = *a4;
            int *a5  = a7+4*a2;
            --a3;
            if (a6>t1) {
                L6:
                a0=*a5;
                *a5=a6;
                --a2;
                *a4=a0;
            }
            a4-=4;
        } while (a1<a3);

        a0=a4;
        a2 *=4;
        t1 = *t3;
        a7+=a2;
        int a5 = *a7;
        *a7 = t1;
        *t3 = a5;
        goto L6;
        
    } else {
    a0 = a2;
    a2 = a2<<2;
    a7 = a7 + a2;
    int a5 = *a7; 
    *a7 = t1;
    *t3 = a5;
    }
    return t3;
}


// int foo(int* a0, int a1, int a2) {
//     int* t3= a0 + ((a1<<32)>>30);
//     int t1 = *t3;
//     int* a7 = a0;
//     int a3;
//     if (a1 < a2) {
//         int* a4 = a0 +(a2<<2);
//         a3 = a2;

//         do {
//             int a6 = *a4;
//             int *a5  = a7+(a2 <<2);
//             --a3;
//             if (a6>t1) {
//                 L6:
//                 a0=*a5;
//                 *a5=a6;
//                 --a2;
//                 *a4=a0;
//             }
//             a4-=4;
//         } while (a1<a3);

//         a0=a4;
//         a2 = a2 <<2;
//         t1 = *t3;
//         a7+=a2;
//         int a5 = *a7;
//         *a7 = t1;
//         *t3 = a5;
//         goto L6;
        
//     } else {
//     a0 = a2;
//     a2 = a2<<2;
//     a7 = a7 + a2;
//     int a5 = *a7; 
//     *a7 = t1;
//     *t3 = a5;
//     }
//     return t3;
// }


// int foo(int* a0, int a1, int a2) {
//     int* t3= a0 + ((a1<<32)>>30);
//     int t1 = *t3; // t1 = a0[a1*4]
//     int* a7 = a0;
//     int a3;
//     if (a1 < a2) {
//         int* a4 = a0 +(a2<<2); // a4 = a2*4
//         a3 = a2;

//         L4:
//         int a6 = *a4;
//         int *a5  = a7+(a2 <<2); //a5+=a7;  //
//         --a3;
//         if (a6>t1) {
            
//         L6:
//         a0=*a5;
//         *a5=a6;
//         --a2;
//         *a4=a0;
//         goto L3;
//         } else {
//         L3:
//         a4-=4;
//         if (a1<a3) goto L4;
//         a0=a4;
//         a2 = a2 <<2; // a2*=4
//         t1 = *t3;
//         a7+=a2; // ??
//         a5 = *a7;
//         *a7 = t1;
//         *t3 = a4;
//         goto L6;
//         }
//     }
//     else {
//     a0 = a2;
//     a2 = a2<<2;
//     a7 +=a2;// ??
//     int a5 = *a7; 
//     *a7 = t1;
//     *t3 = a5;
//     }
// return a3;
// }
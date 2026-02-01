foo:
  mv  a3,a0
  blt a0,zero,.L4
  li  a0,1
  ble a3,a0,.L1
  mv  a5,a0
  mv  a4,a0
.L3:
  mv  a2,a0
  addi  a5,a5,1
  add a0,a0,a4
  mv  a4,a2
  bne a3,a5,.L3
  ret
.L4:
  li  a0,0
.L1:
  ret



int foo(int x) {
    if (x < 0) return 0;
    if (x <= 1) return 1;
    int a3 = x;
    x = 1;
    int a5 = 1;
    int a4 = 1;
    while(a3 != a5) {
        int a2 = x;
        ++a5;
        x+=a4;
        a4=a2;
    }
    return x;
}
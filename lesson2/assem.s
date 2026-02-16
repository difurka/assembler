foo:
  slli  a5,a1,32
  srli  t3,a5,30
  add t3,a0,t3
  lw  t1,0(t3)
  mv  a7,a0
  bgeu  a1,a2,.L5
  slli  a4,a2,2
  add a4,a0,a4
  mv  a3,a2
.L4:
  lw  a6,0(a4)
  slli  a5,a2,2
  add a5,a7,a5
  addiw a3,a3,-1
  ble a6,t1,.L3
  lw  a0,0(a5)
  sw  a6,0(a5)
  addiw a2,a2,-1
  sw  a0,0(a4)
.L3:
  addi  a4,a4,-4
  bltu  a1,a3,.L4
  mv  a0,a2
  slli  a2,a2,2
  lw  t1,0(t3)
  add a7,a7,a2
  lw  a5,0(a7)
  sw  t1,0(a7)
  sw  a5,0(t3)
  ret
.L5:
  mv  a0,a2
  slli  a2,a2,2
  add a7,a7,a2
  lw  a5,0(a7)
  sw  t1,0(a7)
  sw  a5,0(t3)
  ret
.globl solution

#Fормула для вычислений будет выведена ниже (arr[i] - элемент массива, считаем что arr[-1] == 0):
#ЕСЛИ ((arr[3] - arr[2] & arr[4]) > 569)
#ТО (arr[i] = arr[i - 1] & 33)
#ИНАЧЕ (arr[i] = arr[i] ^ 32)



solution:
# a1 - адрес памяти, где расположен массив
# a2 - количество элементов в массиве
mv a3, a1 # begin
mv a4, a2 # size
loop:
ld a5, 24(a1) # a5 <-a[3]
ld a6, 16(a1) # a6<-a[2]
ld a7, 32(a1) # a7<-a[4]

sub a5,a5,a6
and a5,a5,a7 # a5<-(arr[3] - arr[2]) & arr[4]
li a6, 569 # a6<- 569

blt a6, a5, success_case
ld a7, 0(a3) # a7<-a[i]
xori a7, a7, 32
sd a7, 0(a3) # a[i] = a7
add a3, a3, 8 # ++begin
j final

success_case:
beq a3, a1, first_elem
ld a7, -8(a3)
j success_proc

first_elem:
li a7, 0

success_proc:
andi a7, a7, 33
sd a7, 0(a3) # a[i]=arr[i - 1] & 33
add a3, a3, 8 # ++begin

final:
addi a2,a2,-1 
bgtz a2, loop
ret

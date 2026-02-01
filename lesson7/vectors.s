.globl solution

solution:
# a0 -- arr1
# a1 -- arr2
# a2 -- arr3
# a3 -- arr4
# a4 -- len (количество элементов в массивах)
# a5 -- res (указатель на массив с результатом)
# используются 32-битные элементы массива

vsetvli t0, a4, e32
vle32.v v0, (a0) # считать группу элементов из arr1
sub a4, a4, t0  # уменьшить счетчик элементов
slli t0, t0, 2  # t0 <- t0 << 2 (t0 *= 4)
add a0, a0, t0  # сдвинуть указатель *arr1 на следующую группу

vle32.v v1, (a1) # считать группу элементов из arr2
add a1, a1, t0  # сдвинуть указатель *arr2 на следующую группу

vle32.v v2, (a2) # считать группу элементов из arr3
add a2, a2, t0  # сдвинуть указатель *arr3 на следующую группу

vle32.v v3, (a3) # считать группу элементов из arr3
add a3, a3, t0  # сдвинуть указатель *arr4 на следующую группу

# arr2 & (arr2 | (arr3 - arr4 * arr2) & arr3 * (arr3 * arr3) + arr2)

vmul.vv v4, v2, v2 # v4 <- arr3 * arr3
vmul.vv v4, v4, v2 # v4 <- arr3 * (arr3 * arr3)
vadd.vv v4, v4, v1 # v4 <- v4 + a2
vmul.vv v5, v3, v1 # v5 <- arr4 * arr2
vsub.vv v5, v2, v5 # v5 <- arr3 - v5
vand.vv v4, v4, v5 # v4 <- v4 & v5
vor.vv v4, v1, v4  # v4 <- arr2 | v4
vand.vv v4, v1, v4 # v4 <- arr2 & v4

vse32.v v4, (a5) # сохранить результат в *res

add a5, a5, t0  # сдвинуть указатель *zs на следующие элементы
bgt a4, x0, solution  # если n = 0, то остались ещё элементы

ret
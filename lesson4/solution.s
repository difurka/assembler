.globl main
.text

# example
# 1. Замените все цифры в строке остатками их деления на 7 
# 2. Замените каждый пробел на число символов “_” в исходной строке. Если число больше 6, то укажите его остаток от деления на 14
# 3. Перевести все согласные ['B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'] в нижний регистр

# my
# 1. Замените каждый пробел на число символов “_” в исходной строке. Если число больше 7, то укажите его остаток от деления на 14
# 2. Перевести все согласные ['B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'] в нижний регистр
# 3. Замените все цифры в строке остатками их деления на 9

# For all functions:
# a0 - return value (if any)
# a2 - string 1 input address
# a3 - number of underscores mod 14
# t0..t6 - temp values
# Which fits RISC-V conventions

main:
li a0, 0
la a1, str
li a2, 255
li a7, 63
ecall         # ecall for string read

la a2, str      # a2 <- string address
call solve      # process string

call strlen      # get string length

mv t0, a0       # t0 <- string length
li a0, 1
la a1, str
mv a2, t0
li a7, 64
ecall         # ecall for string print

li a0, 0
li a7, 93
ecall         # ecall to exit program

# get string length
# returns string's length in a0
strlen:
mv t0, zero      # t0 <- 0
mv t3, zero      # t3 <- 0
mv t1, a2       # t1 <- string
j cond_strlen     # do

loop_strlen:       
addi t0, t0, 1    # ++t0 (count)
addi t1, t1, 1    # ++t1 (address)

cond_strlen:        
lb t2, 0(t1)     # t2 <- str[t1]
bnez t2, loop_strlen # while not '\0'

mv a0, t0       # a0 <- t0 (strlen)
ret          # return

underscores_count:
mv t1, a2       # t1 <- string
mv t3, zero      # t3 <- 0
li t4, 95       # t4 <- '_' ASCII code
li t5, 14       # t5 <- 14 (mod value)
j cond_uc       # do

loop_uc:
addi t1, t1, 1    # ++t1 (address)

cond_uc:
lb t2, 0(t1)     # t2 <- str[t1]
beqz t2, cond_mod14  # break if '\0'

bne t2, t4, loop_uc  # if t2 is '_'

addi t3, t3, 1    # ++t3
j loop_uc       # while(1)


loop_mod14:
addi t3, t3, -14   # t3 -= 14

cond_mod14:
bge t3, t5, loop_mod14 # if t3 > 14


end_count:
mv a0, t3       # a0 <- t3
ret          # return

# replace digits as: y = x % 9
mod9:
mv t1, a2       # t1 <- string
li t4, 57       # t4 <- '9' ASCII code
# ; li t5, 57       # t5 <- '9' ASCII code
j cond_mod9      # do

loop_mod9:
addi t1, t1, 1    # next symbol

cond_mod9:
lb t3, 0(t1)     # t3 <- str[t1]
beqz t3, ret_mod9   # break if '\0'
blt t3, t4, loop_mod9 # skip if t3 < '9'
bgt t3, t4, loop_mod9 # or if t3 > '9'
addi t3, t3, -9    # else t3 -= 9
sb t3, 0(t1)     # str[t1] = t3
j loop_mod9      # while(1)

ret_mod9:
ret          # return

# replace spaces as number
space_replace:
mv t1, a2       # t1 <- string
j cond_sr       # do

loop_sr:
addi t1, t1, 1    # next symbol

cond_sr:
lb t2, 0(t1)     # t2 <- str[t1]
beqz t2, ret_rs    # break if '\0'
li t3, 32       # t3 <- space ASCII code
bne t2, t3, loop_sr  # if not space skip process

mv t5, a3       # t5 <- number of '_' % 14
li t3, 10       # t3 <- 10
blt t5, t3, blt_10  # if t5 < 10 skip shifting
addi t5, t5, -10   # t5 -= 10 (get last digit)

#shift string and insert '1'
mv t4, t1       # t4 <- t1

search_end:        # do
lb t6, 0(t4)     # t6 <- str[t4]
beqz t6, shift_str  # if t6 =='\0' break
addi t4, t4, 1    # ++t4
j search_end     # while (1)

shift_str:        # do
lb t6, 0(t4)     # t6 <- str[t4]
sb t6, 1(t4)     # str[t4+1] <- t6
addi t4, t4, -1    # --t4
bne t4, t1, shift_str # while t4 != t1

li t6, 49       # t6 <- '1' ASCII code
sb t6, 0(t1)     # str[t1] <- t6
addi t1, t1, 1    # ++t1

blt_10:
addi t5, t5, 48    # t5 += 48 (digit -> ASCII)
sb t5, 0(t1)     # str[t1] <- t5
j loop_sr       # while

ret_rs:
ret

# consonants to lowercase
lowercase_cons:
mv t1, a2       # t1 <- string
j cond_lc       # do

loop_lc:
addi t1, t1, 1    # next symbol

cond_lc:
lb t3, 0(t1)     # t3 <- str[t1]
beqz t3, ret_lc    # break if '\0'

li t4, 65       # t4 <- 'A' ASCII code
blt t3, t4, loop_lc  # if t3 < 'A' skip

li t4, 90       # t4 <- 'Z' ASCII code
bgt t3, t4, loop_lc  # if t3 > 'Z' skip

li t4, 65       # t4 <- 'A' ASCII code
beq t3, t4, loop_lc  # if t3 == 'A' skip

li t4, 69       # t4 <- 'E' ASCII code
beq t3, t4, loop_lc  # if t3 == 'E' skip

li t4, 73       # t4 <- 'I' ASCII code
beq t3, t4, loop_lc  # if t3 == 'I' skip

li t4, 79       # t4 <- 'O' ASCII code
beq t3, t4, loop_lc  # if t3 == 'O' skip

li t4, 85       # t4 <- 'U' ASCII code
beq t3, t4, loop_lc  # if t3 == 'U' skip

li t4, 89       # t4 <- 'Y' ASCII code
beq t3, t4, loop_lc  # if t3 == 'Y' skip

addi t3, t3, 32    # t3 += 0x20 (convert)
sb t3, 0(t1)     # str[t1] <- t3

j loop_lc       # while(1)

ret_lc:
ret          # return

solve:
addi sp, sp, -16   # allocate 16 bytes on
# stack
sw  ra, 12(sp)    # store return address on
# stack
call underscores_count # a0 <- number of '_' % 14
mv a3, a0       # a3 <- a0

call mod9       # replace digits
call space_replace  # replace spaces with a3
call lowercase_cons  # convert consonants

lw  ra, 12(sp)    # load return address from
# stack
addi sp, sp, 16    # restore stack pointer
ret          # return

.data
str:
.zero 256       # string buffer

.equ write, 64    # Номер системного вызова write() = 64
.equ exit, 93     # Номер системного вызова exit() = 93

.section .text    # Переключаемся в сегмент исполняемого кода
.globl _start     # Делаем метку _start глобальной (точка входа)

_start:
li a0, 1           # a0 = 1 (stdout — стандартный вывод)
la a1, msgbegin    # a1 = адрес строки "Hello World!\n"
lbu a2, msgsize    # a2 = размер строки (загружаем байт из msgsize)
li a7, write       # a7 = 64 (номер syscall write)
ecall              # Выполнить системный вызов!

li a0, 0           # a0 = 0 (код возврата программы)
li a7, exit        # a7 = 93 (номер syscall exit)
ecall              # Завершить программу

.section .rodata   # Read-Only Data (константы)

msgbegin:
.ascii "Hello World!\n"  # Массив ASCII байтов (13 символов)

msgsize:
.byte .-msgbegin  # Размер = текущий адрес - адрес msgbegin

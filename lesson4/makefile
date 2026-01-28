all:
	riscv64-linux-gnu-as hello.s -o hello.o
	riscv64-linux-gnu-ld hello.o -o hello
	./hello

djb2_my:
	riscv64-linux-gnu-as djb2.s -o djb2.o
	riscv64-linux-gnu-gcc djb2.o -o djb2
# 	export QEMU_LD_PREFIX=/usr/riscv64-linux-gnu/
	qemu-riscv64-static djb2
# 	./djb2

CC=riscv64-linux-gnu-gcc
AS=riscv64-linux-gnu-as

djb2: djb2.o
	$(CC) djb2.o -o djb2 -static

djb2.o: djb2.s
	$(AS) djb2.s -o djb2.o

run: djb2
	./djb2

clean:
	rm -f *.o djb2

.PHONY: run clean

word:
	riscv64-linux-gnu-as -o wordcount.o wordcount.s
	riscv64-linux-gnu-gcc -o wordcount wordcount.o
	export QEMU_LD_PREFIX=/usr/riscv64-linux-gnu/
# 	qemu-riscv64-static wordcount << text.txt
	./wordcount << text.txt

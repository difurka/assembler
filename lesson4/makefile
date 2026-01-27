all:
	riscv64-linux-gnu-as hello.s -o hello.o
	riscv64-linux-gnu-ld hello.o -o hello
	./hello

djb2:
	riscv64-linux-gnu-as djb2.s -o djb2.o
	riscv64-linux-gnu-gcc djb2.o -o djb2
# 	export QEMU_LD_PREFIX=/usr/riscv64-linux-gnu/
# 	qemu-riscv64-static djb2

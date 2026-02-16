all:
	gcc -O0 -g -c instruction.c
	gcc -O0 -g decoder.c instruction.o
	./a.out < input_decoder.txt

encoder:
	gcc -O0 -g -c instruction.c
	gcc -O0 -g encoder.c instruction.o
	./a.out < input.txt

bib:
	gcc -O0 -g -c instruction.c

prob:
	gcc -O0 -g problem1.c
	./a.out < input2.txt
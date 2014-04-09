kernel: start.o kernel.o linker.ld
	ld -melf_i386 -T linker.ld -o kernel start.o kernel.o

start.o: start.s
	nasm -f elf start.s # -g

kernel.o: kernel.c
	gcc -ffreestanding -c kernel.c

clean:
	rm -f *.o kernel

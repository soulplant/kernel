kernel: kernel.o linker.ld
	ld -melf_i386 -T linker.ld -o kernel kernel.o

kernel.o: kernel.s
	nasm -f elf -g kernel.s

clean:
	rm -f *.o kernel

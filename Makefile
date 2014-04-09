CXX=g++
CXXFLAGS=-std=c++11 -fno-exceptions -fno-rtti -ffreestanding -c
INCLUDES=screen.h
OBJ=start.o kernel.o screen.o runtime.o
kernel: $(OBJ) linker.ld
	ld -melf_i386 -T linker.ld -o kernel $(OBJ)

start.o: start.s
	nasm -f elf start.s # -g

screen.o: screen.cc $(INCLUDES)
	$(CXX) $(CXXFLAGS) screen.cc

runtime.o: runtime.cc $(INCLUDES)
	$(CXX) $(CXXFLAGS) runtime.cc

kernel.o: kernel.c $(INCLUDES)
	$(CXX) $(CXXFLAGS) kernel.c
	# g++ -std=c++11 -fno-exceptions -fno-rtti -ffreestanding -c kernel.c

clean:
	rm -f *.o kernel

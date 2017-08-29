CC=gcc -m32 -O -fno-exceptions -fno-pie
FLAGS=-Wall
asmfiles=$(wildcard *.asm)
bins=$(asmfiles:.asm=.bin)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
LD=ld -m elf_i386
QEMU=qemu-system-i386

all: floppy

floppy: bootsect.bin kernel
	cat $^ /dev/zero | dd of=$@ bs=512 count=2880

kernel: $(OBJ)
	$(LD) -Ttext 1000 --oformat binary kernel.o screen.o -o $@

bootsect.bin: bootsect.asm
	nasm -f bin -o $@ $<

%o: %.c
	$(CC) $FLAGS -o $@ $<

###########
run: floppy
	$(QEMU) -boot a -fda $<

clean:
	@rm -f $(bins)
	@rm -f floppy
	@rm -f *~
	@rm -f kernel

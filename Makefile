CFLAGS = -Iinclude -std=gnu99 -O2

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.asm
	nasm -felf64 $<

SRC_C = $(wildcard *.c)
SRC_ASM = $(wildcard *.asm)

OBJ = $(SRC_C:.c=.o) $(SRC_ASM:.asm=.o)

simple_c_server: $(OBJ)
	$(CC) -pthread -o $@ $+

.PHONY: clean
clean:
	rm -f *.o simple_c_server

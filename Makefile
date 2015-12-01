CFLAGS=-Iinclude -std=c99

%.o: %.c
	$(CC) $(CFLAGS) -c $<

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

simple_c_server: $(OBJ)
	$(CC) -o $@ $+

.PHONY: clean
clean:
	rm -f *.o simple_c_server

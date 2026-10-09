CC 		= gcc
CFLAGS  = -Wall -g

main.exe: main.o matrix.o
	$(CC) $(CFLAGS) -o $@ $^ 

main.o: main.c matrix.h pow_iter.c rayleigh_quot_iter.c shift_inv_pow_iter.c
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

clean:
	rm -f main.exe *.o
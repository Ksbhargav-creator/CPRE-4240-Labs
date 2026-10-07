CC = gcc
CFLAGS = -O2 -Wall -D_DEFAULT_SOURCE
LDLIBS = -lm

main.exe: main.o matrix.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

main.o: main.c matrix.h
matrix.o: matrix.c matrix.h

clean:
	rm -f main.exe *.o
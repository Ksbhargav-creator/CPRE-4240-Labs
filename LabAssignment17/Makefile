CC = gcc
FFLAGS = -Wall -O3 -std=c99 -fopenmp
LFLAGS = -fopenmp

OBJECTS = blur.o

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) *.exe
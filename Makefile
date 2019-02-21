CC = gcc
CFLAGS = -Wall
DEPS = FileFilters.h

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: cls.o FileFilters.o
	$(CC) -o cls cls.o FileFilters.o

clean:
	rm -rf cls *.o

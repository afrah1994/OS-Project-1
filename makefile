CC=gcc

all: dt

dt: dt.o
	$(CC) -o dt dt.o

dt.o:dt.c
	$(CC) -c dt.c

clean:
	rm -rf *o dt
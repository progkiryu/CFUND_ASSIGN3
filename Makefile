CC = gcc
CFLAGS = -Wall -Werror -ansi -lm

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

grade: grade.o
	$(CC) $(CFLAGS) -o grade grade.o

grade.o: grade.c grade.h
	$(CC) $(CFLAGS) -c grade.c

clean:
	rm -f main grade *.o
CC = gcc
CFLAGS = -Wall -Werror -ansi -lm

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

grade: grade.o
	$(CC) $(CFLAGS) -o grade grade.o

grade.o: grade.c system.h
	$(CC) $(CFLAGS) -c grade.c

student: student.o
	$(CC) $(CFLAGS) -o student student.o

student.o: student.c system.h
	$(CC) $(CFLAGS) -c student.c	

file: file.o
	$(CC) $(CFLAGS) -o file file.o

file.o: file.c system.h
	$(CC) $(CFLAGS) -c file.c

compression: compression.o
	$(CC) $(CFLAGS) -o compression compression.o

compression.o: compression.c system.h
	$(CC) $(CFLAGS) -c compression.c

encryption: encryption.o
	$(CC) $(CFLAGS) -o encryption encryption.o

encryption.o: encryption.c system.h
	$(CC) $(CFLAGS) -c encryption.c

clean:
	rm -f main grade student file compression *.o

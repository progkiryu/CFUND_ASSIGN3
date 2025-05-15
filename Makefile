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

saveToFile.o: saveToFile.c system.h
	$(CC) $(CFLAGS) -c saveToFile.c

clean:
	rm -f main grade student *.o

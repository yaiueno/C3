OBJS = main.o interface.o arithmetic.o
CC = gcc

mytest: $(OBJS)
	$(CC) $(OBJS) -o mytest

main.o: main.c test.h
	$(CC) -c main.c

interface.o: interface.c test.h
	$(CC) -c interface.c

arithmetic.o: arithmetic.c test.h
	$(CC) -c arithmetic.c

clean:
	rm -f $(OBJS) mytest

OBJS = main.o array_operations.o
CC = gcc

array_test: $(OBJS)
	$(CC) $(OBJS) -o array_test

main.o: main.c C1.h
	$(CC) -c main.c

array_operations.o: array_operations.c C1.h
	$(CC) -c array_operations.c

clean:
	rm -f $(OBJS) array_test

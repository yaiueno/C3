OBJS = main.o array_operations.o core_operations.o
CC = gcc

mycore_operations: $(OBJS)
	$(CC) $(OBJS) -o mycore_operations
main.o: main.c C4.h
	$(CC) -c main.c
array_operations.o: array_operations.c C4.h
	$(CC) -c array_operations.c
core_operations.o: core_operations.c C4.h
	$(CC) -c core_operations.c
clean:
	rm -f $(OBJS) mycore_operations
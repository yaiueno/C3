OBJS = main.o que_operations.c
CC = gcc

myque_test:$(OBJS)
	$(CC) $(OBJS) -o myque_test
main.o: main.c C3.h
	$(CC) -c main.c
que_opereations.o: que_operations.c C3.h
	$(CC) -c que_operations.c
clean:
	rm -f $(OBJS) myque_test
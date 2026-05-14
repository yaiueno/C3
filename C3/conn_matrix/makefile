OBJS = main.o graph_as_matrix.o array_operations.o que_operations.o
CC = gcc

myconnectivity: $(OBJS)
	$(CC) $(OBJS) -o myconnectivity
main.o: main.c C3.h
	$(CC) -c main.c
array_operations.o: array_operations.c C3.h
	$(CC) -c array_operations.c
graph_as_matrix.o: graph_as_matrix.c C3.h
	$(CC) -c graph_as_matrix.c
que_operations.o: que_operations.c C3.h
	$(CC) -c que_operations.c
clean:
	rm -f $(OBJS) myconnectivity
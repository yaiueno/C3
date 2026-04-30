OBJS = main.o graph_as_matrix.o
CC = gcc

myread_as_matirx: $(OBJS)
	$(CC) $(OBJS) -o myread_as_matrix
main.o: main.c C3.h
	$(CC) -c main.c
graph_as_matrix.o: graph_as_matrix.c C3.h
	$(CC) -c graph_as_matrix.c
clean:
	rm -f $(OBJS) myread_as_matrix
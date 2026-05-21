OBJS = main.o graph_as_list.o array_operations.o core_operations.o
CC = gcc 
mydijkstra: $(OBJS)
	$(CC) $(OBJS) -o mydijkstra
main.o: main.c C4.h
	$(CC) -c main.c
graph_as_list.o: graph_as_list.c C4.h
	$(CC) -c graph_as_list.c
array_operations.o: array_operations.c C4.h
	$(CC) -c array_operations.c
core_operations.o: core_operations.c C4.h
	$(CC) -c core_operations.c
clean:
	rm -f $(OBJS) mydijkstra
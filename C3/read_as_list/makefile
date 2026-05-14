OBJS = main.o graph_as_list.o
CC = gcc

read_as_list: $(OBJS)
	$(CC) $(OBJS) -o myread_as_list
main.o: main.c C3.h
	$(CC) -c main.c
graph_as_list.o: graph_as_list.c C3.h
	$(CC) -c graph_as_list.c
clean:
	rm -f $(OBJS) myread_as_list
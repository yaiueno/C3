OBJS = main.o graph_as_list.o
CC = gcc

myread_as_list:$(OBJS)
	$(CC) $(OBJS) -o myread_as_Alist
main.o: main.c C4.h
	$(CC) -c main.c
graph_as_list.o: graph_as_list.c C4.h
	$(CC) -c graph_as_list.c
clean:
	rm -f $(OBJS) myread_as_Alist
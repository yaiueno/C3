OBJS = main.o array_operations.o sort.o
CC = gcc

myselection_sort: $(OBJS)
	$(CC) $(OBJS) -o myselection_sort 
main.o: main.c C2.h
	$(CC) -c main.c
array_operations.o: array_operations.c C2.h
	$(CC) -c array_operations.c
sort.o: sort.c C2.h
	$(CC) -c sort.c
clean:
	rm -f $(OBJS) myselecrtion_sort
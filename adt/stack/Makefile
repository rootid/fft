OBJS = main.o Stack.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic $(DEBUG)

myStack : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o myStack 

Stack.o: Stack.h Stack.cpp
	$(CC) -c $(CFLAGS) Stack.cpp

main.o: main.cpp Stack.h 
	$(CC) -c $(CFLAGS) main.cpp

clean:
	rm -f *.o a.out myStack 

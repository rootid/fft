OBJS = NodeList.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic $(DEBUG)

myList : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o myList 

main.o: main.cpp NodeList.h 
	$(CC) -c $(CFLAGS) main.cpp

NodeList.o: Node.h NodeList.h 
	$(CC) -c $(CFLAGS) NodeList.cpp

clean:
	rm -f *.o a.out myList 

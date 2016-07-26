OBJS = window.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -pedantic $(DEBUG)

window : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o window 

window.o: window.h 
	$(CC) -c $(CFLAGS) window.cpp

clean:
	rm -f *.o a.out window 

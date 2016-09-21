MAKEFILE = Makefile
CC = gcc
CFLAGS = -ggdb # -O4 -g -DNDEBUG -pg
LFLAGS = -lm # -g -lm -pg

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)
BINARIES = 8-queens permutations subsets war sorting bfs-demo \
	dfs-demo connected topsort prim dijkstra floyd findcycle stringedit \
	lcs substringedit superman convex-hull triangulate 10055 distance name \
	polly gcd primes bignum editbrute elevator order plates geotest cgtest \
	netflow
INCLUDES = bool.h backtrack.h queue.h graph.h wgraph.h editdistance.h \
	   geometry.h

make:	$(BINARIES)
	
$(OBJECTS):     $(INCLUDES)
 
$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)

8-queens:	backtrack.o 8-queens.o
		#$(__BREAKPOINT)
		$(CC) -o $@ 8-queens.o backtrack.o $(LFLAGS)

permutations:	backtrack.o permutations.o
		$(CC) -o $@ permutations.o backtrack.o $(LFLAGS)

subsets:	backtrack.o subsets.o
		$(CC) -o $@ subsets.o backtrack.o $(LFLAGS)

sorting:	random.o sorting.o
		$(CC) -o $@ random.o sorting.o $(LFLAGS)

war:		queue.o random.o war.o
		$(CC) -o $@ queue.o random.o war.o $(LFLAGS)

bignum:		bignum.o
		$(CC) -o $@ bignum.o $(LFLAGS)

bfs-demo:	queue.o graph.o bfs-dfs.o bfs-demo.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o bfs-demo.o $(LFLAGS)

dfs-demo:	queue.o graph.o bfs-dfs.o dfs-demo.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o dfs-demo.o $(LFLAGS)

connected:	queue.o graph.o bfs-dfs.o connected.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o connected.o $(LFLAGS)

topsort:	queue.o graph.o topsort.o
		$(CC) -o $@ queue.o graph.o topsort.o $(LFLAGS)

findcycle:	queue.o graph.o bfs-dfs.o findcycle.o
		$(CC) -o $@ queue.o graph.o bfs-dfs.o findcycle.o $(LFLAGS)

prim:		wgraph.o prim.o
		$(CC) -o $@ wgraph.o prim.o $(LFLAGS)

dijkstra:	wgraph.o dijkstra.o
		$(CC) -o $@ wgraph.o dijkstra.o $(LFLAGS)

floyd:		floyd.o
		$(CC) -o $@ floyd.o $(LFLAGS)

editbrute:	editbrute.o stringedit.o
		$(CC) -o $@ editbrute.o stringedit.o $(LFLAGS)

stringedit:	editdistance.o stringedit.o
		$(CC) -o $@ editdistance.o stringedit.o $(LFLAGS)

lcs:		editdistance.o lcs.o
		$(CC) -o $@ editdistance.o lcs.o $(LFLAGS)

substringedit:	editdistance.o substringedit.o
		$(CC) -o $@ editdistance.o substringedit.o $(LFLAGS)

superman:	geometry.o superman.o
		$(CC) -o $@ geometry.o superman.o $(LFLAGS)

convex-hull:	geometry.o convex-hull.o
		$(CC) -o $@ geometry.o convex-hull.o $(LFLAGS)

triangulate:	geometry.o triangulate.o
		$(CC) -o $@ geometry.o triangulate.o $(LFLAGS)

10055:		10055.o
		$(CC) -o $@ 10055.o $(LFLAGS)

distance:	distance.o
		$(CC) -o $@ distance.o $(LFLAGS)

name:		name.o
		$(CC) -o $@ name.o $(LFLAGS)

polly:		polly.o
		$(CC) -o $@ polly.o $(LFLAGS)

gcd:		gcd.o
		$(CC) -o $@ gcd.o $(LFLAGS)

primes:		primes.o
		$(CC) -o $@ primes.o $(LFLAGS)

elevator:	elevator.o
		$(CC) -o $@ elevator.o $(LFLAGS)

plates:		plates.o
		$(CC) -o $@ plates.o $(LFLAGS)

order:		order.o
		$(CC) -o $@ order.o $(LFLAGS)

geotest:	geometry.o geotest.o
		$(CC) -o $@ geometry.o geotest.o $(LFLAGS)

cgtest:		geometry.o cgtest.o
		$(CC) -o $@ geometry.o cgtest.o $(LFLAGS)

netflow:	netflow.o queue.o
		$(CC) -o $@ netflow.o queue.o $(LFLAGS)


lint:	
	lint -h $(SOURCES)

backup:	$(SOURCES) $(INCLUDES)
	cp $(SOURCES) backup
	cp $(INCLUDES) backup
 
clean: 	
	rm -f core *.o a.out $(BINARIES)

tar:	
	make clean
	tar cvf /tmp/bookprograms.tar .

#	Steven Skiena
#	March 26, 2002
#	Makefile for all "Programming Challenges" Book Programs
#

# Copyright 2003 by Steven S. Skiena; all rights reserved. 
#
# Permission is granted for use in non-commerical applications
# provided this copyright notice remains intact and unchanged.
#


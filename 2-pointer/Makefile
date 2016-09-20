SHELL = /bin/sh
CXX = g++
CPPFLAGS += -isystem $(GTEST_DIR)/include
CPPFLAGS = -I include
CXXFLAGS += -g -Wall -Wextra -pthread


all : main

main: intersection.o main.cpp
	$(CXX) $^ -o $@

intersection.o : intersection.cpp
		$(CXX) -c $< -o $@
.PHONY: clean
clean :
	rm -f main *.o

#target: prereq1 prereq2
#      commands
# $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1.cc
#
#intersection.o : intersection.cpp
#		$(CXX) -c intersection.cpp

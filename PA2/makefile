# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/mps
	@echo -n ""

bin/mps 	    : planar.o main_mps.o
			$(CC) $(OPTFLAGS) planar.o main_mps.o -o bin/mps

main_mps.o      : src/main.cpp
			$(CC) $(CFLAGS) $< -o $@

planar.o		:src/planar.cpp src/planar.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

#####################################
# @author: Abdullah Emad 			#
# Makefile for The binary heap test #
#####################################

# compiler to use
CC = clang

# flags to pass compiler
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# name for executable
EXE = bin/cranbheap

# space-separated list of header files
HDRS = include/cranbheap.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS = -lcunit

# space-separated list of source files
SRCS = src/cranbheap.c src/lib/*.c


# Included folders
INCLUDES = include


# automatically generated list of object files
OBJS = $(SRCS:.c=.o)



###########################################
#   Compile object files into a library   #
###########################################

# default target make
default: compile createlib indexlib
	
# creates the object file
compile:
	$(CC) $(CFLAGS) -c $(SRCS) -I $(INCLUDES)

#creates the library
createlib: 
	ar rc libcranbheap.a cranbheap.o

#create index on the library
indexlib: 
	ranlib libcranbheap.a

# dependencies 
$(OBJS): $(HDRS) Makefile



###################################
# Install in the correct locations#
###################################
install: 
	mkdir -p /usr/local/include/cranberry && \
	cp $(HDRS) /usr/local/include/cranberry/cranbheap.h && \
	cp libcranbheap.a /usr/local/lib/libcranbheap.a

uninstall: 
	rm -f /usr/local/include/cranberry/cranbheap.h && \
	rm -f /usr/local/lib/libcranbheap.a && \
	rmdir --ignore-fail-on-non-empty /usr/local/include/cranberry

###############################
#		Test and cli		  #
#	   for developers		  #
###############################


#Creates binary for the test in /bin
test: mkbin
	$(CC) $(CFLAGS) test/test.c $(LIBS) $(SRCS) -o bin/test -I $(INCLUDES)

#Creates binary for the cli in /bin
cli: mkbin
	$(CC) $(CFLAGS) $(SRCS) cli/cli.c  -o bin/cli -I $(INCLUDES)

#creates the bin directory if it does not exist
mkbin:
	mkdir -p bin

#Fix any code styling issue
beautiful: 
	indent -bad -bap -nbc -bbo -hnl -brs -c33 -cd33 -ncdb -ci4 -cli0 -d0 -bls -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -npsl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1 -bli0 src/*.c src/lib/* src/compacted/*.c include/*.h test/*.c && rm -rf include/*~* src/*~* src/lib/*~* src/compacted/*~* test/*~*

# housekeeping
clean:
	rm -f core *.o *.a bin/cli bin/test

.PHONY: test cli


cc=gcc
cflags=-g -std=c2x -Wall -Werror

libdir=lib/shared
libs_names := $(shell find $(libdir)/ -name \*.so) 

run: $(f) 
	rm -f run
	$(cc) $< $(cflags) -lm -L$(libdir) $(libs_names) -o run
	./run



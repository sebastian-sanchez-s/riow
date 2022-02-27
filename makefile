cc=gcc
cflags=-g -std=c2x -Wall -Werror

libdir=lib/shared
libs_names := $(shell find $(libdir)/ -name \*.so) 

run: $(f) 
	$(cc) $< $(cflags) -lm -L$(libdir) $(libs_names) -o run
	./run



cc = gcc
cflags = -g -std=c2x -Wall -Werror

sources = $(shell ls | egrep .c)

objdir = objects
objects = $(patsubst %.c,$(objdir)/%.o,$(sources))

shareddir = shared
sharedobj = $(patsubst %.c,$(shareddir)/lib%.so,$(sources))

.PHONY: all

all: $(objects) $(sharedobj) | $(objdir) $(shareddir)

$(shareddir)/lib%.so: $(objdir)/%.o
	$(cc) $< -shared -o $@

$(objdir)/%.o: %.c 
	$(cc) $< -c $(cflags) -fpic -o $@ 

$(shareddir):
	mkdir $(shareddir)

$(objdir):
	mkdir $(objdir) 


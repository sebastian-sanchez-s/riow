CC=gcc
CF=-c -Wall -Werror -std=c99
CL=-lm
OBJ=vector.o ray.o

all: libmath.a

libmath.a: $(OBJ)
	ar -rcs $@ $^
	rm *.o

%: %.c
	$(CC) $(CF) $(CL) $<

CC=gcc
MT=-I../math -L../math -lmath -lm
FS=-Wall -Werror -c -g -std=c99
OB=camera.o

all: libcamera.a

libcamera.a: $(OB)
	ar -rcs $@ $^
	rm *.o

%.o: %.c
	echo $<
	$(CC) $< $(MT) $(FS)

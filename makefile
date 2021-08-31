CC=gcc
GRAPHICS=-Ilib/graphic/includes -Llib/graphic/ -lbmp
MATH=-Ilib/math/ -Llib/math -lmath -lm
FLAGS=-g -std=c99

%: %.c
	$(CC) $< $(FLAGS) $(GRAPHICS) $(MATH) -o app

run: app
	./app

clean:
	rm app

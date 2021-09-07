CC=gcc
GRAPHICS=-Ilib/graphic/includes -Llib/graphic/ -lbmp
MATH=-Ilib/math/ -Llib/math -lmath -lm
HITT=-Ilib/hittables -Llib/hittables -lhittables
FLAGS=-g -std=c99

%: %.c
	$(CC) $< $(FLAGS) $(GRAPHICS) $(HITT) $(MATH) -o app

run: app
	./app

clean:
	rm app

default:
	clear && make build && make run

clean:
	clear && rm bin/*

build:
	gcc -std=gnu11 -pedantic -W -Wall -Wextra main.c tlib.c -o bin/lab4

run:
	bin/lab4

debug:
	clear && make dbuild && make drun

dbuild:
	gcc -g -std=gnu11 -pedantic -W -Wall -Wextra main.c tlib.c -o bin/lab4_debug

drun:
	gdb bin/lab4_debug
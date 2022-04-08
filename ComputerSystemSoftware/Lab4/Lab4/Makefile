default:
	clear && make build && make run

clean:
	clear && rm gcc/*

build:
	gcc -std=gnu11 -pedantic -W -Wall -Wextra main.c -o gcc/lab4

run:
	gcc/lab4

debug:
	clear && make dbuild && make drun

dbuild:
	gcc -g -std=gnu11 -pedantic -W -Wall -Wextra main.c -o gcc/lab4_debug

drun:
	gdb gcc/lab4_debug
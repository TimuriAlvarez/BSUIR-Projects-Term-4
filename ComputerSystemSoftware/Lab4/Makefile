default:
	clear && make build && make run

build:
	gcc -std=gnu11 -pedantic -W -Wall -Wextra *.c -o bin/lab

run:
	bin/lab


debug:
	clear && make dbuild && make drun

dbuild:
	gcc -g -std=gnu11 -pedantic -W -Wall -Wextra *.c -o bin/lab_debug

drun:
	gdb bin/lab_debug


clean:
	clear && rm bin/*

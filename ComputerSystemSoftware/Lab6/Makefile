default:
	make clean
	make build
	read T_ARG
	make run

build:
	gcc -std=gnu11 -pedantic -W -Wall -Wextra sources/*.c -o bin/lab -lpthread

run:
	bin/lab


debug:
	clear && make dbuild && make drun

dbuild:
	gcc -g -std=gnu11 -pedantic -W -Wall -Wextra sources/*.c -o bin/lab_debug -lpthread

drun:
	gdb bin/lab_debug


clean:
	clear
	rm -f bin/*
	rm -f resources/grey_plain_*.bmp
	rm -f resources/grey_threads_*.bmp

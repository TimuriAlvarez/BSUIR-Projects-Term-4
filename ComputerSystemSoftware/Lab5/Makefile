default:
	make build
	make run
build:
	clear
	gcc sources/main.c sources/tlib.c -o bin/lab --std=gnu11 -pthread -lrt
	gcc sources/producer.c sources/tlib.c -o bin/producer -pthread
	gcc sources/taker.c sources/tlib.c -o bin/taker -pthread
	cp -rf bin sources
run:
	bin/lab
debug:
	make dbuild
	make drun
dbuild:
	clear
	gcc sources/main.c sources/tlib.c -o bin/lab_debug -g --std=gnu11 -pthread -lrt
	gcc sources/producer.c sources/tlib.c -o bin/producer_debug -g -pthread
	gcc sources/taker.c sources/tlib.c -o bin/taker_debug -g -pthread
drun:
	bin/lab
clear:
	rm -rf bin/*
	rm -rf sources/bin/*
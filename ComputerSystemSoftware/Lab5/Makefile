# Makefile
CC		= gcc
VERSION	= c11
OPTIONS	= -pedantic -W -Wall -Wextra
FLAGS	= -pthread
SRC		= sources/circle.c sources/tlib.c
SRC1	= sources/main.c $(SRC)
SRC2	= sources/producer.c $(SRC)
SRC3	= sources/taker.c $(SRC)
NUMBER	= 5
NAME1	= lab$(NUMBER)
NAME2	= producer
NAME3	= taker
# Arguments to be paseed in programm
args	=

help:
	# 	Make options:
	# about		-	Get general information about the lab;
	# tor		-	Read Terms of Reference;
	# build		-	Build binary ready for execution;
	# run		-	Execute binary;
	# dbuild	-	Build binary ready for debug;
	# debug		-	Debug binary;
	# clean		-	Remove all build and temporary files.

about:
	# Year:			2nd
	# Term:			4th
	# Subject:		Computer System Software
	# Project:		Lab $(NUMBER)
	# OS:			Linux (WSL)

tor:
	nano -v +93 ../README.md

build:
	clear
	$(CC) -std=$(VERSION) $(OPTIONS) $(SRC1) -o bin/$(NAME1) $(FLAGS)
	$(CC) -std=$(VERSION) $(OPTIONS) $(SRC2) -o bin/$(NAME2) $(FLAGS)
	$(CC) -std=$(VERSION) $(OPTIONS) $(SRC3) -o bin/$(NAME3) $(FLAGS)

dbuild:
	clear
	$(CC) -std=$(VERSION) $(OPTIONS) $(SRC1) -o bin/$(NAME1)_debug $(FLAGS) -g
	$(CC) -std=$(VERSION) $(OPTIONS) $(SRC2) -o bin/$(NAME2)_debug $(FLAGS) -g
	$(CC) -std=$(VERSION) $(OPTIONS) $(SRC3) -o bin/$(NAME3)_debug $(FLAGS) -g

run:
	make build
	bin/$(NAME1) $(args)

debug:
	make dbuild
	bin/$(NAME1)_debug $(args)

clean:
	clear
	rm -f bin/*
	rm -f temp/*

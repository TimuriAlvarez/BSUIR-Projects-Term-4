# Makefile
CC		= gcc
VERSION	= gnu11
OPTIONS	= -pedantic -W -Wall -Wextra
FLAGS	= 
SRC		= src/*.c
NUMBER	= 9
NAME	= lab$(NUMBER)
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
	#
	# generate	-	Generate all required files

about:
	# Year:			2nd
	# Term:			4th
	# Subject:		Computer System Software
	# Project:		Lab $(NUMBER)
	# OS:			Linux (WSL)

tor:
	nano -v +156 ../README.md

build:
	clear
	$(CC) -std=$(VERSION) $(OPTIONS) $(SRC) -o bin/$(NAME) $(FLAGS)

dbuild:
	clear
	$(CC) -std=$(VERSION) $(OPTIONS) $(SRC) -o bin/$(NAME)_debug $(FLAGS) -g

run:
	make build
	bin/$(NAME) $(args)

debug:
	make dbuild
	gdb bin/$(NAME)_debug $(args)

clean:
	clear
	rm -f bin/*
	rm -f tmp/*

generate:
	cp -f res/* tmp

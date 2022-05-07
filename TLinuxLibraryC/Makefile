# Makefile
CC		= gcc
VERSION	= c11
OPTIONS	= -pedantic -W -Wall -Wextra
FLAGS	= -lpthread
SRC		= sources/main.c sources/tlib.c
NAME	= tlinux
# Arguments to be paseed in programm
args	=

help:
	# 	Make options:
	# about				-	Get general information about the lab;
	# tor				-	Read Terms of Reference;
	# build				-	Build binary ready for execution;
	# run [args=...]		-	Execute binary (with command-line arguments if provided);
	# 					To send multiple arguments use "arg1 arg2 ..." or 'arg1 arg2 ...';
	# dbuild			-	Build binary ready for debug;
	# debug				-	Debug binary;
	# clean				-	Remove all build and temporary files.

about:
	# Year:			2nd
	# Term:			4th
	# Subject:		Computer System Software
	# Project:		TLinux
	# OS:			Linux (WSL)
	#				Windows (only as interface for Linux headers)

tor:
	nano -v README.md

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
	bin/$(NAME)_debug $(args)

clean:
	clear
	rm -f bin/*
	rm -f temp/*

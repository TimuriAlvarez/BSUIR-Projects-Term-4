TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		*.c \
		sources/main.c

HEADERS += \
		*.h \
		sources/*.h \
		sources/tbasic/*.h \
		sources/tbasic/tnumeric.h \
		sources/tconio/*.h \
		sources/tfilesystem/*.h \
		sources/timport/*.h

DISTFILES += \
		sources/t*.c \
		sources/tbasic/*.c \
		sources/tconio/*.c \
		sources/tfilesystem/*.c \
		sources/timport/*.c
		Makefile

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		tlinux.c \
		sources/main.c \
		sources/tlib.c

DISTFILES += \
		*.c \
		sources/*.c \
		sources/tfilesystem/*.c \
		sources/tinterface/*.c \
		sources/tinterface/sys/*.c \
		sources/tipc/*.c \
		sources/tthreads/*.c

HEADERS += \
		*.h \
		sources/*.h \
		sources/tfilesystem/*.h \
		sources/tinterface/*.h \
		sources/tinterface/sys/*.h \
		sources/tipc/*.h \
		sources/tthreads/*.h

DISTFILES += \
		Makefile

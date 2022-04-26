TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	sources/*.c \
	sources/threads.c

HEADERS += \
	sources/*.h \
	sources/threads.h

DISTFILES += \
	resources/* \
	temp/* \
	README.md \
	Makefile

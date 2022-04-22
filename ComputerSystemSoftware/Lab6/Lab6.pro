TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	sources/*.c \
	sources/threads.c

DISTFILES += \
	README.md \
	Makefile

HEADERS += \
	sources/*.h \
	sources/threads.h

RESOURCES += \
	resources/*

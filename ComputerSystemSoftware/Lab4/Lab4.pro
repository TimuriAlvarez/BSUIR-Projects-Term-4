TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		sources/*.c \
		sources/memory.c

HEADERS += \
		sources/*.h \
		sources/child.h \
		sources/memory.h \
		sources/parent.h

DISTFILES += \
		Makefile \
		README.md


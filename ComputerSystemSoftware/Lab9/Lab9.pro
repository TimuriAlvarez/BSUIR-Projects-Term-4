TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		sources/main.c \
		sources/menu.c \
		sources/tlib.c \
		sources/tthread.c

HEADERS += \
		sources/*.h \
		sources/tthread.h

DISTFILES += \
		Makefile \
		README.md

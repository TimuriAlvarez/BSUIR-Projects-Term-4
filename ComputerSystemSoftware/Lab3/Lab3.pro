TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		sources/*.c \
		sources/ring.c

HEADERS += \
		sources/*.h

DISTFILES += \
		Makefile \
		README.md

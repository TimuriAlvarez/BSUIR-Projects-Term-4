TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		sources/circle.c \
		sources/main.c \
		sources/producer.c \
		sources/taker.c \
		sources/tlib.c

HEADERS += \
		sources/*.h

DISTFILES += \
		Makefile \
		README.md

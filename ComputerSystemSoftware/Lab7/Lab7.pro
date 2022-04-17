TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	sources/*.c \
	sources/*.asm

DISTFILES += \
	README.md \
	Makefile

HEADERS += \
	sources/*.h

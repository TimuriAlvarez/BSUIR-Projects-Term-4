TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	sources/*.cpp

DISTFILES += \
	scripts/* \
	Makefile

HEADERS += \
	sources/*.h \
	../dos.h

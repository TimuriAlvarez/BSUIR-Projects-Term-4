TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		sources/*.c

HEADERS += \
		sources/*.h \
		sources/thread.h

DISTFILES += \
		Makefile \
		README.md

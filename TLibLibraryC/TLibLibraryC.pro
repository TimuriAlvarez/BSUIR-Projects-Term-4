TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	sources/*.c \
	sources/tbasic/*.c \
	sources/tcontainer/*.c \
	sources/timport/*.c \
	sources/tconio/*.c

HEADERS += \
	sources/*.h \
	sources/tbasic/*.h \
	sources/tcontainer/*.h \
	sources/timport/*.h \
	sources/tconio/*.h

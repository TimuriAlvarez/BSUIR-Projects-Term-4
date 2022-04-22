TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		*.c

DISTFILES += \
		import/* \
		sources/*.c \
		sources/tbasic/*.c \
		sources/timport/*.c \
		sources/timport/tcontainer/*.c \
		sources/tconio/*.c \
		sources/tfilesystem/*.c

HEADERS += \
		*.h \
		sources/*.h \
		sources/tbasic/*.h \
		sources/timport/*.h \
		sources/timport/tcontainer/*.h \
		sources/tconio/*.h \
		sources/tfilesystem/*.h \
		sources/ttimer.h

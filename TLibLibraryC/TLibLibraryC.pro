TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		*.c

HEADERS += \
		*.h \
		sources/*.h \
		sources/tbasic/*.h \
		sources/tconio/*.h \
		sources/tfilesystem/*.h \
		sources/timport/*.h

DISTFILES += \
		*.c \
		sources/*.c \
		sources/tbasic/*.c \
		sources/tconio/*.c \
		sources/tfilesystem/*.c \
		sources/timport/*.c

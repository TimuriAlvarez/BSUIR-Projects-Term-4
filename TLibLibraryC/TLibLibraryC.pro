TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	*.c \
	sources/*.c \
	sources/tbasic/*.c \
	sources/tcontainer/*.c \
	sources/timport/*.c \
	sources/tconio/*.c \
	sources/tfilesystem/*.c

HEADERS += \
	*.h \
	sources/*.h \
	sources/tbasic/*.h \
	sources/tcontainer/*.h \
	sources/timport/*.h \
	sources/tconio/*.h \
	sources/tfilesystem/*.h

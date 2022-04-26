TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		*.c \
		sources/*.c \
		sources/tfilesystem/*.c \
		sources/tinterface/*.c \
		sources/tinterface/sys/*.c

HEADERS += \
		*.h \
		sources/*.h \
		sources/tfilesystem/*.h \
		sources/tinterface/*.h \
		sources/tinterface/sys/*.h

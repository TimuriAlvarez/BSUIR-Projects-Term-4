TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
		*.c

HEADERS += \
		*.h \
		sources/*.h \
		sources/semaphore.h \
		sources/sys.h \
		sources/sys/*.h \
		sources/sys/ipc.h \
		sources/sys/shm.h \
		sources/sys/stat.h

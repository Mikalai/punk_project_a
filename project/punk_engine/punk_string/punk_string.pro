include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_string

LIBS += -L$${LIBDIR} -lpunk_error
INCLUDEPATH += ../../../source

HEADERS += \
    ../../../source/string/buffer_error.h \
    ../../../source/string/buffer.h \
    ../../../source/string/string_error.h \
    ../../../source/string/string_list.h \
    ../../../source/string/string.h \
    ../../../source/string/module.h

SOURCES += \
    ../../../source/string/buffer_error.cpp \
    ../../../source/string/buffer.cpp \
    ../../../source/string/string_error.cpp \
    ../../../source/string/string.cpp \
    ../../../source/string/string_list.cpp


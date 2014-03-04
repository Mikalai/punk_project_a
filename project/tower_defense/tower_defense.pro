include(../punk_common.pri)

INCLUDEPATH += ../../source
TEMPLATE = app
TARGET = punk_core

INCLUDEPATH += ../../../source

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string

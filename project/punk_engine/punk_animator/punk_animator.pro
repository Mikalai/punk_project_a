######################################################################
# Automatically generated by qmake (2.01a) ?? 25. ??? 19:53:26 2013
######################################################################

include(../punk_common.pri)

CONFIG += dll
TEMPLATE = lib
TARGET = punk_animator

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string -lpunk_core -lpunk_math -lpunk_system -lpunk_attributes -lpunk_ai -lpunk_scene

INCLUDEPATH += ../../../source

HEADERS += \
    ../../../source/animator/ianimator_module.h \
    ../../../source/animator/ianimator_observer.h \
    ../../../source/animator/ianimator_processor.h \
    ../../../source/animator/module.h

SOURCES += \
    ../../../source/animator/ianimator_module.cpp


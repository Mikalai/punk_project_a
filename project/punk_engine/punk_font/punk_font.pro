include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_string

LIBS += -lfreetype
LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string

INCLUDEPATH += ../../../source

HEADERS += \
    ../../../source/fonts/font_builder_interface.h \
    ../../../source/fonts/font_builder.h \
    ../../../source/fonts/font_manager_component.h \
    ../../../source/fonts/module.h

SOURCES += \
    ../../../source/fonts/font_builder.cpp \
    ../../../source/fonts/font_manager_component.cpp

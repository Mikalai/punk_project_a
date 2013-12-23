include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_font

DEFINES += USE_FREETYPE

contains(DEFINES, USE_FREETYPE) {
    LIBS += -L$${LIB_3RD} -lfreetype
    INCLUDEPATH += $${INCLUDE_3RD}/freetype/include
}

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string -lpunk_system -lpunk_core

INCLUDEPATH += ../../../source

HEADERS += \
    ../../../source/fonts/font_builder_interface.h \
    ../../../source/fonts/font_builder.h \
    ../../../source/fonts/font_manager_component.h \
    ../../../source/fonts/module.h \
    ../../../source/fonts/font_error.h

SOURCES += \
    ../../../source/fonts/font_builder.cpp \
    ../../../source/fonts/font_manager_component.cpp \
    ../../../source/fonts/font_error.cpp

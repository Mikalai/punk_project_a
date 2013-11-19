######################################################################
# Automatically generated by qmake (2.01a) ?? 25. ??? 19:53:26 2013
######################################################################

include(../punk_common.pri)

CONFIG += dll
TEMPLATE = lib
TARGET = punk_math

INCLUDEPATH += ../../../source

CONFIG(debug, debug|release) {
    LIBS += -L../../../bin/debug/ -lpunk_error -lpunk_string
} else {
    LIBS += -L../../../bin/release/ -lpunk_error -lpunk_string
}

SOURCES += \    
    ../../../source/math/vec4.cpp \
    ../../../source/math/vec3.cpp \
    ../../../source/math/vec2.cpp \
    ../../../source/math/mat4.cpp \
    ../../../source/math/mat3.cpp \
    ../../../source/math/mat2.cpp \
    ../../../source/math/quat.cpp \
    ../../../source/math/math_error.cpp


HEADERS += \
    ../../../source/math/vec4.h \
    ../../../source/math/vec3.h \
    ../../../source/math/vec2.h \
    ../../../source/math/mat4.h \
    ../../../source/math/mat3.h \
    ../../../source/math/mat2.h \
    ../../../source/math/quat.h \
    ../../../source/math/math_error.h

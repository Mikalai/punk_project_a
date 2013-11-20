######################################################################
# Automatically generated by qmake (2.01a) ?? 25. ??? 19:53:26 2013
######################################################################

#*g++* : QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,\$\$ORIGIN/\'
QMAKE_CXXFLAGS += -std=c++11 -pipe

INCLUDEPATH += ../source

CONFIG -= QT

TEMPLATE = app
TARGET = punk_tests

SOURCES += \
    ../source/tests/main.cpp \
    ../source/tests/punk/engine/core/buffer_test.cpp \
    ../source/tests/punk/engine/core/string_test.cpp \
    ../source/tests/punk/engine/core/string_list_test.cpp \
    ../source/tests/punk/engine/math/vec2_test.cpp \
    ../source/tests/punk/engine/math/vec3_test.cpp \
    ../source/tests/punk/engine/math/vec4_test.cpp \
    ../source/tests/punk/engine/math/mat2_test.cpp \
    ../source/tests/punk/engine/math/mat3_test.cpp


win32 {
    INCLUDEPATH += D:\sdk\cppunit-1.12.1\include\
}

unix {
CONFIG(debug, debug|release) {
    LIBS += -L../bin/debug/ -lpunk_error -lpunk_string -lpunk_math
    LIBS += -lgcov -lcppunit

    DESTDIR = ../bin/debug
} else {
    LIBS += -lgcov -lcppunit -L../bin/release/ -lpunk_error -lpunk_string -lpunk_math
    DESTDIR = ../bin/release
}
}

HEADERS += \
    ../source/tests/punk/engine/core/buffer_test.h \
    ../source/tests/punk/engine/core/string_test.h \
    ../source/tests/punk/engine/core/string_list_test.h \
    ../source/tests/punk/engine/math/vec2_test.h \
    ../source/tests/punk/engine/math/vec3_test.h \
    ../source/tests/punk/engine/math/vec4_test.h \
    ../source/tests/punk/engine/math/mat2_test.h \
    ../source/tests/punk/engine/math/mat3_test.h

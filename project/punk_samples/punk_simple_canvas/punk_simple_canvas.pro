######################################################################
# Automatically generated by qmake (2.01a) ?? 25. ??? 19:53:26 2013
######################################################################

#*g++* : QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,\$\$ORIGIN/\'
QMAKE_CXXFLAGS += -std=c++11 -pipe

INCLUDEPATH += ../../../source

CONFIG -= qt

TEMPLATE = app
TARGET = punk_simple_canvas

CONFIG(debug, debug|release) {
    LIBS += -L../../../../bin/debug/ -lpunk_error -lpunk_string -lpunk_math -lpunk_core -lpunk_system -lpunk_graphics
    DESTDIR = ../../../../bin/debug
} else {
    LIBS += -L../../../../bin/release/ -lpunk_error -lpunk_string -lpunk_math -lpunk_core -lpunk_system -lpunk_graphics
    DESTDIR = ../../../../bin/release
}

SOURCES += \
    ../../../source/samples/simple_canvas/main.cpp

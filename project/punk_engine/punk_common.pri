CONFIG += debug_and_release
CONFIG -= QT

QMAKE_CXXFLAGS += -std=c++11 -pipe

win32 {
    DEFINES += WIN32
}

unix {
    DEFINES += __gnu_linux__
}

DEFINES += PUNK_ENGINE_EXPORTS


CONFIG(debug, debug|release) {
    DESTDIR = ../../../../bin/debug
    LIBDIR = ../../../../bin/debug
}
else {
    DESTDIR = ../../../../bin/release
    LIBDIR = ../../../../bin/release
}

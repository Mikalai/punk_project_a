######################################################################
# Automatically generated by qmake (2.01a) ?? 25. ??? 19:53:26 2013
######################################################################

include(../punk_common.pri)

CONFIG += dll
TEMPLATE = lib
TARGET = punk_graphics

unix {
    LIBS += -lX11
}

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string -lpunk_core -lpunk_system -lopengl32 -lgdi32

INCLUDEPATH += ../../../source

HEADERS += \
    ../../../source/graphics/config.h \
    ../../../source/graphics/module.h \
    ../../../source/graphics/canvas/canvas.h \
    ../../../source/graphics/canvas/canvas_desciption.h \
    ../../../source/graphics/error/module.h \
    ../../../source/graphics/error/graphics_error.h \
    ../../../source/graphics/opengl/gl/glcorearb.h \
    ../../../source/graphics/opengl/gl/glext.h \
    ../../../source/graphics/opengl/gl/glxext.h \
    ../../../source/graphics/opengl/gl/wglext.h \
    ../../../source/graphics/opengl/extensions.h \
    ../../../source/graphics/canvas/module.h \
    ../../../source/graphics/canvas/canvas_interface.h

SOURCES += \
    ../../../source/graphics/gpu_common_module.cpp \
    ../../../source/graphics/gpu_module.cpp \
    ../../../source/graphics/canvas/canvas.cpp \
    ../../../source/graphics/canvas/canvas_desciption.cpp \
    ../../../source/graphics/error/graphics_error.cpp \
    ../../../source/graphics/opengl/extensions.cpp

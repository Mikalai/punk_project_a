######################################################################
# Automatically generated by qmake (2.01a) ?? 25. ??? 19:53:26 2013
######################################################################

include(../punk_common.pri)

CONFIG += dll
TEMPLATE = lib
TARGET = punk_render

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string -lpunk_core -lpunk_math -lpunk_system -lpunk_attributes -lpunk_ai -lpunk_scene -lpunk_graphics

INCLUDEPATH += ../../../source

HEADERS += \
    ../../../source/render/error/module.h \
    ../../../source/render/singlethreaded/irender_module.h \
    ../../../source/render/singlethreaded/irender_observer.h \
    ../../../source/render/singlethreaded/irender_processor.h \
    ../../../source/render/singlethreaded/module.h \
    ../../../source/render/singlethreaded/render_cache.h \
    ../../../source/render/singlethreaded/render_commands.h \
    ../../../source/render/singlethreaded/render_observer.h \
    ../../../source/render/module.h

SOURCES += \
    ../../../source/render/singlethreaded/irender_module.cpp \
    ../../../source/render/singlethreaded/render_commands.cpp \
    ../../../source/render/singlethreaded/render_observer.cpp


include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_gui

INCLUDEPATH += ../../../source

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string -lpunk_system -lpunk_core -lpunk_image -lpunk_math

HEADERS += \
    ../../../source/gui/widgets/button.h \
    ../../../source/gui/widgets/container_widget.h \
    ../../../source/gui/widgets/image.h \
    ../../../source/gui/widgets/manager.h \
    ../../../source/gui/widgets/module.h \
    ../../../source/gui/widgets/widget.h \
    ../../../source/gui/common/font_manager.h \
    ../../../source/gui/common/input_device.h \
    ../../../source/gui/common/module.h \
    ../../../source/gui/common/picture.h \
    ../../../source/gui/common/render.h \
    ../../../source/gui/common/style.h \
    ../../../source/gui/common/widget_render.h

SOURCES += \
    ../../../source/gui/widgets/button.cpp \
    ../../../source/gui/widgets/container_widget.cpp \
    ../../../source/gui/widgets/image.cpp \
    ../../../source/gui/widgets/manager.cpp \
    ../../../source/gui/widgets/widget.cpp \
    ../../../source/gui/common/style.cpp \
    ../../../source/gui/common/widget_render.cpp

######################################################################
# Automatically generated by qmake (2.01a) ?? 25. ??? 19:53:26 2013
######################################################################

include(../punk_common.pri)

CONFIG += dll
TEMPLATE = lib
TARGET = punk_terminal

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string -lpunk_core

INCLUDEPATH += ../../../source

HEADERS += \
    ../../../source/terminal/command.h \
    ../../../source/terminal/command_processor.h \
    ../../../source/terminal/module.h \
    ../../../source/terminal/terminal_commands/cmd_help.h

SOURCES += \
    ../../../source/terminal/command.cpp \
    ../../../source/terminal/command_processor.cpp \
    ../../../source/terminal/terminal_commands/cmd_help.cpp


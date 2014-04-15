include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_blender

INCLUDEPATH += ../../../source

OTHER_FILES += \
    ../../../source/blender/punk_engine_tools/__init__.py

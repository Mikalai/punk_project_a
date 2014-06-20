include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_core

INCLUDEPATH += ../../../source

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string

HEADERS += \
    ../../../source/core/compound_object.h \
    ../../../source/core/container.h \
    ../../../source/core/factory.h \
    ../../../source/core/guid.h \
    ../../../source/core/icompound_object.h \
    ../../../source/core/ifactory.h \
    ../../../source/core/iobject.h \
    ../../../source/core/object_pool.h \
    ../../../source/core/action.h \
    ../../../source/core/atomicint.h \
    ../../../source/core/core_error.h \
    ../../../source/core/decl_property.h \
    ../../../source/core/meta_class.h \
    ../../../source/core/meta_class_base.h \
    ../../../source/core/module.h \
    ../../../source/core/object.h \
    ../../../source/core/pool.h \
    ../../../source/core/poolable.h \
    ../../../source/core/pool_manager.h \
    ../../../source/core/rtti.h \
    ../../../source/core/static_information.h

SOURCES += \
    ../../../source/core/guid.cpp \
    ../../../source/core/ifactory.cpp \
    ../../../source/core/compound_object.cpp \
    ../../../source/core/core_error.cpp \
    ../../../source/core/meta_class_base.cpp \
    ../../../source/core/object.cpp \
    ../../../source/core/pool_manager.cpp \
    ../../../source/core/rtti.cpp \
    ../../../source/core/static_information.cpp


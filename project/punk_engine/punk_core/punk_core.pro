include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_core

INCLUDEPATH += ../../../source

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string

HEADERS += \
    ../../../source/core/action.h \
    ../../../source/core/object.h \
    ../../../source/core/decl_property.h \
    ../../../source/core/meta_class_base.h \
    ../../../source/core/meta_class.h \
    ../../../source/core/module.h \
    ../../../source/core/object.h \
    ../../../source/core/pool_manager.h \
    ../../../source/core/pool.h \
    ../../../source/core/poolable.h \
    ../../../source/core/rtti.h \
    ../../../source/core/static_information.h \
    ../../../source/core/core_error.h \
    ../../../source/core/atomicint.h \
    ../../../source/core/component/component.h \
    ../../../source/core/component/components_pool_impl.h \
    ../../../source/core/component/components_pool.h \
    ../../../source/core/component/module.h \
    ../../../source/core/component/component_interface.h

SOURCES += \
    ../../../source/core/compound_object.cpp \
    ../../../source/core/meta_class_base.cpp \
    ../../../source/core/object.cpp \
    ../../../source/core/pool_manager.cpp \
    ../../../source/core/pool.cpp \
    ../../../source/core/rtti.cpp \
    ../../../source/core/static_information.cpp \
    ../../../source/core/core_error.cpp \
    ../../../source/core/component/component.cpp \
    ../../../source/core/component/components_pool_impl.cpp \
    ../../../source/core/component/components_pool.cpp

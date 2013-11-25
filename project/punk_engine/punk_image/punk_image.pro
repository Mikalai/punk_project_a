include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_image

INCLUDEPATH += ../../../source

#   Enable support for tiff images
DEFINES += USE_LIB_TIFF
#   Enable support for jpeg images
DEFINES += USE_LIB_JPEG
#   Enable support for png images
DEFINES += USE_LIB_PNG

contains(DEFINES, USE_LIB_TIFF) {
LIBS += -ltiff
}


LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string

HEADERS += \
    ../../../source/images/png_file.h \
    ../../../source/images/formats.h \
    ../../../source/images/image_file.h \
    ../../../source/images/module.h \
    ../../../source/images/internal_images/component.h \
    ../../../source/images/internal_images/gray_image.h \
    ../../../source/images/internal_images/image_impl.h \
    ../../../source/images/internal_images/image.h \
    ../../../source/images/internal_images/rgb_image.h \
    ../../../source/images/internal_images/rgba_image.h \
    ../../../source/images/import_export/exporter.h \
    ../../../source/images/import_export/importer_impl.h \
    ../../../source/images/import_export/importer.h \
    ../../../source/images/import_export/jpg_importer.h \
    ../../../source/images/import_export/openexr_importer.h \
    ../../../source/images/import_export/png_exporter.h \
    ../../../source/images/import_export/png_importer.h \
    ../../../source/images/import_export/tiff_importer.h \
    ../../../source/images/error/image_exceptions.h \
    ../../../source/images/error/module.h \
    ../../../source/images/converter/yuy2_to_rgb.h

SOURCES += \
    ../../../source/images/image_file.cpp \
    ../../../source/images/png_file.cpp \
    ../../../source/images/internal_images/gray_image.cpp \
    ../../../source/images/internal_images/image.cpp \
    ../../../source/images/internal_images/rgb_image.cpp \
    ../../../source/images/internal_images/rgba_image.cpp \
    ../../../source/images/import_export/exporter.cpp \
    ../../../source/images/import_export/importer.cpp \
    ../../../source/images/import_export/jpg_importer.cpp \
    ../../../source/images/import_export/openexr_importer.cpp \
    ../../../source/images/import_export/png_exporter.cpp \
    ../../../source/images/import_export/png_importer.cpp \
    ../../../source/images/import_export/tiff_importer.cpp \
    ../../../source/images/converter/yuy2_to_rgb.cpp

OTHER_FILES += \
    ../../../source/images/converter/yuy2_to_rgb.cl


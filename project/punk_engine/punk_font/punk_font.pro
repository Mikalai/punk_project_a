include(../punk_common.pri)

INCLUDEPATH += ../../source
CONFIG += dll
TEMPLATE = lib
TARGET = punk_font

DEFINES += USE_FREETYPE

contains(DEFINES, USE_FREETYPE) {    
    INCLUDEPATH += ../../../source/fonts/freetype/include
    DEFINES += FT_DEBUG_LEVEL_TRACE FT2_BUILD_LIBRARY
}

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string -lpunk_system -lpunk_core

INCLUDEPATH += ../../../source

HEADERS += \
    ../../../source/fonts/font_builder_interface.h \
    ../../../source/fonts/font_builder.h \
    ../../../source/fonts/font_manager_component.h \
    ../../../source/fonts/module.h \
    ../../../source/fonts/font_error.h \
    ../../../source/fonts/freetype/include/ft2build.h \
    ../../../source/fonts/freetype/include/config/ftconfig.h \
    ../../../source/fonts/freetype/include/config/ftheader.h \
    ../../../source/fonts/freetype/include/config/ftmodule.h \
    ../../../source/fonts/freetype/include/config/ftoption.h \
    ../../../source/fonts/freetype/include/config/ftstdlib.h

SOURCES += \
    ../../../source/fonts/font_builder.cpp \
    ../../../source/fonts/font_manager_component.cpp \
    ../../../source/fonts/font_error.cpp \
    ../../../source/fonts/freetype/src/base/ftbbox.c \
    ../../../source/fonts/freetype/src/base/ftgxval.c \
    ../../../source/fonts/freetype/src/base/ftlcdfil.c \
    ../../../source/fonts/freetype/src/base/ftmm.c \
    ../../../source/fonts/freetype/src/base/ftotval.c \
    ../../../source/fonts/freetype/src/base/ftpatent.c \
    ../../../source/fonts/freetype/src/base/ftpfr.c \
    ../../../source/fonts/freetype/src/base/ftsynth.c \
    ../../../source/fonts/freetype/src/base/fttype1.c \
    ../../../source/fonts/freetype/src/base/ftwinfnt.c \
    ../../../source/fonts/freetype/src/base/ftxf86.c \
    ../../../source/fonts/freetype/src/pcf/pcf.c \
    ../../../source/fonts/freetype/src/pfr/pfr.c \
    ../../../source/fonts/freetype/src/psaux/psaux.c \
    ../../../source/fonts/freetype/src/pshinter/pshinter.c \
    ../../../source/fonts/freetype/src/psnames/psmodule.c \
    ../../../source/fonts/freetype/src/raster/raster.c \
    ../../../source/fonts/freetype/src/sfnt/sfnt.c \
    ../../../source/fonts/freetype/src/truetype/truetype.c \
    ../../../source/fonts/freetype/src/type1/type1.c \
    ../../../source/fonts/freetype/src/cid/type1cid.c \
    ../../../source/fonts/freetype/src/type42/type42.c \
    ../../../source/fonts/freetype/src/winfonts/winfnt.c \
    ../../../source/fonts/freetype/src/autofit/autofit.c \
    ../../../source/fonts/freetype/src/bdf/bdf.c \
    ../../../source/fonts/freetype/src/cff/cff.c \
    ../../../source/fonts/freetype/src/base/ftbase.c \
    ../../../source/fonts/freetype/src/base/ftbitmap.c \
    ../../../source/fonts/freetype/src/cache/ftcache.c \
    ../../../source/fonts/freetype/src/ftdebug.c \
    ../../../source/fonts/freetype/src/base/ftfstype.c \
    ../../../source/fonts/freetype/src/base/ftgasp.c \
    ../../../source/fonts/freetype/src/base/ftglyph.c \
    ../../../source/fonts/freetype/src/gzip/ftgzip.c \
    ../../../source/fonts/freetype/src/base/ftinit.c \
    ../../../source/fonts/freetype/src/lzw/ftlzw.c \
    ../../../source/fonts/freetype/src/base/ftstroke.c \
    ../../../source/fonts/freetype/src/base/ftsystem.c \
    ../../../source/fonts/freetype/src/smooth/smooth.c

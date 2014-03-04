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

LIBS += -L$${LIBDIR} -lpunk_error -lpunk_string -lpunk_system

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

contains(DEFINES, USE_LIB_PNG)
{
HEADERS += \
    ../../../source/images/import_export/libpng/png.h \
    ../../../source/images/import_export/libpng/pngconf.h \
    ../../../source/images/import_export/libpng/pngdebug.h \
    ../../../source/images/import_export/libpng/pnginfo.h \
    ../../../source/images/import_export/libpng/pnglibconf.h \
    ../../../source/images/import_export/libpng/pngpriv.h \
    ../../../source/images/import_export/libpng/pngstruct.h \
    ../../../source/images/import_export/zlib/crc32.h \
    ../../../source/images/import_export/zlib/deflate.h \
    ../../../source/images/import_export/zlib/gzguts.h \
    ../../../source/images/import_export/zlib/inffast.h \
    ../../../source/images/import_export/zlib/inffixed.h \
    ../../../source/images/import_export/zlib/inflate.h \
    ../../../source/images/import_export/zlib/inftrees.h \
    ../../../source/images/import_export/zlib/trees.h \
    ../../../source/images/import_export/zlib/zconf.h \
    ../../../source/images/import_export/zlib/zlib.h \
    ../../../source/images/import_export/zlib/zutil.h

SOURCES += \
    #../../../source/images/import_export/libpng/example.c \
    ../../../source/images/import_export/libpng/png.c \
    ../../../source/images/import_export/libpng/pngerror.c \
    ../../../source/images/import_export/libpng/pngget.c \
    ../../../source/images/import_export/libpng/pngmem.c \
    ../../../source/images/import_export/libpng/pngpread.c \
    ../../../source/images/import_export/libpng/pngread.c \
    ../../../source/images/import_export/libpng/pngrio.c \
    ../../../source/images/import_export/libpng/pngrtran.c \
    ../../../source/images/import_export/libpng/pngrutil.c \
    ../../../source/images/import_export/libpng/pngset.c \
    ../../../source/images/import_export/libpng/pngtest.c \
    ../../../source/images/import_export/libpng/pngtrans.c \
    ../../../source/images/import_export/libpng/pngwio.c \
    ../../../source/images/import_export/libpng/pngwrite.c \
    ../../../source/images/import_export/libpng/pngwtran.c \
    ../../../source/images/import_export/libpng/pngwutil.c \
    ../../../source/images/import_export/zlib/adler32.c \
    ../../../source/images/import_export/zlib/compress.c \
    ../../../source/images/import_export/zlib/crc32.c \
    ../../../source/images/import_export/zlib/deflate.c \
    ../../../source/images/import_export/zlib/gzclose.c \
    ../../../source/images/import_export/zlib/gzlib.c \
    ../../../source/images/import_export/zlib/gzread.c \
    ../../../source/images/import_export/zlib/gzwrite.c \
    ../../../source/images/import_export/zlib/infback.c \
    ../../../source/images/import_export/zlib/inffast.c \
    ../../../source/images/import_export/zlib/inflate.c \
    ../../../source/images/import_export/zlib/inftrees.c \
    ../../../source/images/import_export/zlib/trees.c \
    ../../../source/images/import_export/zlib/uncompr.c \
    ../../../source/images/import_export/zlib/zutil.c
}

contains(DEFINES, USE_LIB_JPEG)
{
HEADERS += \
    ../../../source/images/import_export/libjpeg/cderror.h \
    ../../../source/images/import_export/libjpeg/cdjpeg.h \
    ../../../source/images/import_export/libjpeg/jconfig.h \
    ../../../source/images/import_export/libjpeg/jdct.h \
    ../../../source/images/import_export/libjpeg/jerror.h \
    ../../../source/images/import_export/libjpeg/jinclude.h \
    ../../../source/images/import_export/libjpeg/jmemsys.h \
    ../../../source/images/import_export/libjpeg/jmorecfg.h \
    ../../../source/images/import_export/libjpeg/jpegint.h \
    ../../../source/images/import_export/libjpeg/jpeglib.h \
    ../../../source/images/import_export/libjpeg/jversion.h \
    ../../../source/images/import_export/libjpeg/transupp.h

SOURCES += \
    ../../../source/images/import_export/libjpeg/cdjpeg.c \
    #../../../source/images/import_export/libjpeg/cjpeg.c \
    #../../../source/images/import_export/libjpeg/ckconfig.c \
    #../../../source/images/import_export/libjpeg/djpeg.c \
    #../../../source/images/import_export/libjpeg/example.c \
    ../../../source/images/import_export/libjpeg/jaricom.c \
    #../../../source/images/import_export/libjpeg/jcapimin.c \
    #../../../source/images/import_export/libjpeg/jcapistd.c \
    ../../../source/images/import_export/libjpeg/jcarith.c \
    ../../../source/images/import_export/libjpeg/jccoefct.c \
    ../../../source/images/import_export/libjpeg/jccolor.c \
    ../../../source/images/import_export/libjpeg/jcdctmgr.c \
    ../../../source/images/import_export/libjpeg/jchuff.c \
    ../../../source/images/import_export/libjpeg/jcinit.c \
    ../../../source/images/import_export/libjpeg/jcmainct.c \
    ../../../source/images/import_export/libjpeg/jcmarker.c \
    ../../../source/images/import_export/libjpeg/jcmaster.c \
    ../../../source/images/import_export/libjpeg/jcomapi.c \
    ../../../source/images/import_export/libjpeg/jcparam.c \
    ../../../source/images/import_export/libjpeg/jcprepct.c \
    ../../../source/images/import_export/libjpeg/jcsample.c \
    #../../../source/images/import_export/libjpeg/jctrans.c \
    ../../../source/images/import_export/libjpeg/jdapimin.c \
    ../../../source/images/import_export/libjpeg/jdapistd.c \
    ../../../source/images/import_export/libjpeg/jdarith.c \
    ../../../source/images/import_export/libjpeg/jdatadst.c \
    ../../../source/images/import_export/libjpeg/jdatasrc.c \
    ../../../source/images/import_export/libjpeg/jdcoefct.c \
    ../../../source/images/import_export/libjpeg/jdcolor.c \
    ../../../source/images/import_export/libjpeg/jddctmgr.c \
    ../../../source/images/import_export/libjpeg/jdhuff.c \
    ../../../source/images/import_export/libjpeg/jdinput.c \
    ../../../source/images/import_export/libjpeg/jdmainct.c \
    ../../../source/images/import_export/libjpeg/jdmarker.c \
    ../../../source/images/import_export/libjpeg/jdmaster.c \
    ../../../source/images/import_export/libjpeg/jdmerge.c \
    ../../../source/images/import_export/libjpeg/jdpostct.c \
    ../../../source/images/import_export/libjpeg/jdsample.c \
    ../../../source/images/import_export/libjpeg/jdtrans.c \
    ../../../source/images/import_export/libjpeg/jerror.c \
    ../../../source/images/import_export/libjpeg/jfdctflt.c \
    ../../../source/images/import_export/libjpeg/jfdctfst.c \
    ../../../source/images/import_export/libjpeg/jfdctint.c \
    ../../../source/images/import_export/libjpeg/jidctflt.c \
    ../../../source/images/import_export/libjpeg/jidctfst.c \
    ../../../source/images/import_export/libjpeg/jidctint.c \
    ../../../source/images/import_export/libjpeg/jmemansi.c \
    #../../../source/images/import_export/libjpeg/jmemdos.c \
    #../../../source/images/import_export/libjpeg/jmemmac.c \
    ../../../source/images/import_export/libjpeg/jmemmgr.c \
    #../../../source/images/import_export/libjpeg/jmemname.c \
    #../../../source/images/import_export/libjpeg/jmemnobs.c \
    #../../../source/images/import_export/libjpeg/jpegtran.c \
    ../../../source/images/import_export/libjpeg/jquant1.c \
    ../../../source/images/import_export/libjpeg/jquant2.c \
    ../../../source/images/import_export/libjpeg/jutils.c \
    ../../../source/images/import_export/libjpeg/rdbmp.c \
    ../../../source/images/import_export/libjpeg/rdcolmap.c \
    ../../../source/images/import_export/libjpeg/rdgif.c \
    #../../../source/images/import_export/libjpeg/rdjpgcom.c \
    ../../../source/images/import_export/libjpeg/rdppm.c \
    ../../../source/images/import_export/libjpeg/rdrle.c \
    ../../../source/images/import_export/libjpeg/rdswitch.c \
    ../../../source/images/import_export/libjpeg/rdtarga.c \
    #../../../source/images/import_export/libjpeg/transupp.c \
    ../../../source/images/import_export/libjpeg/wrbmp.c \
    ../../../source/images/import_export/libjpeg/wrgif.c \
    #../../../source/images/import_export/libjpeg/wrjpgcom.c \
    ../../../source/images/import_export/libjpeg/wrppm.c \
    ../../../source/images/import_export/libjpeg/wrrle.c \
    ../../../source/images/import_export/libjpeg/wrtarga.c
}

contains(DEFINES, USE_LIB_TIFF)
{

SOURCES += \
    #../../../source/images/import_export/libtiff/mkg3states.c \
    ../../../source/images/import_export/libtiff/tif_aux.c \
    ../../../source/images/import_export/libtiff/tif_close.c \
    ../../../source/images/import_export/libtiff/tif_codec.c \
    ../../../source/images/import_export/libtiff/tif_color.c \
    ../../../source/images/import_export/libtiff/tif_compress.c \
    ../../../source/images/import_export/libtiff/tif_dir.c \
    ../../../source/images/import_export/libtiff/tif_dirinfo.c \
    ../../../source/images/import_export/libtiff/tif_dirread.c \
    ../../../source/images/import_export/libtiff/tif_dirwrite.c \
    ../../../source/images/import_export/libtiff/tif_dumpmode.c \
    ../../../source/images/import_export/libtiff/tif_error.c \
    ../../../source/images/import_export/libtiff/tif_extension.c \
    ../../../source/images/import_export/libtiff/tif_fax3.c \
    ../../../source/images/import_export/libtiff/tif_fax3sm.c \
    ../../../source/images/import_export/libtiff/tif_flush.c \
    ../../../source/images/import_export/libtiff/tif_getimage.c \
    ../../../source/images/import_export/libtiff/tif_jbig.c \
    ../../../source/images/import_export/libtiff/tif_jpeg.c \
    ../../../source/images/import_export/libtiff/tif_jpeg_12.c \
    ../../../source/images/import_export/libtiff/tif_luv.c \
    ../../../source/images/import_export/libtiff/tif_lzma.c \
    ../../../source/images/import_export/libtiff/tif_lzw.c \
    ../../../source/images/import_export/libtiff/tif_next.c \
    ../../../source/images/import_export/libtiff/tif_ojpeg.c \
    ../../../source/images/import_export/libtiff/tif_open.c \
    ../../../source/images/import_export/libtiff/tif_packbits.c \
    ../../../source/images/import_export/libtiff/tif_pixarlog.c \
    ../../../source/images/import_export/libtiff/tif_predict.c \
    ../../../source/images/import_export/libtiff/tif_print.c \
    ../../../source/images/import_export/libtiff/tif_read.c \
    ../../../source/images/import_export/libtiff/tif_strip.c \
    ../../../source/images/import_export/libtiff/tif_swab.c \
    ../../../source/images/import_export/libtiff/tif_thunder.c \
    ../../../source/images/import_export/libtiff/tif_tile.c \
    #../../../source/images/import_export/libtiff/tif_unix.c \
    ../../../source/images/import_export/libtiff/tif_version.c \
    ../../../source/images/import_export/libtiff/tif_warning.c \
    ../../../source/images/import_export/libtiff/tif_win32.c \
    ../../../source/images/import_export/libtiff/tif_write.c \
    ../../../source/images/import_export/libtiff/tif_zip.c

HEADERS += \
    ../../../source/images/import_export/libtiff/t4.h \
    ../../../source/images/import_export/libtiff/tif_config.h \
    ../../../source/images/import_export/libtiff/tif_config.vc.h \
    ../../../source/images/import_export/libtiff/tif_config.wince.h \
    ../../../source/images/import_export/libtiff/tif_dir.h \
    ../../../source/images/import_export/libtiff/tif_fax3.h \
    ../../../source/images/import_export/libtiff/tif_predict.h \
    ../../../source/images/import_export/libtiff/tiff.h \
    ../../../source/images/import_export/libtiff/tiffconf.h \
    ../../../source/images/import_export/libtiff/tiffconf.vc.h \
    ../../../source/images/import_export/libtiff/tiffconf.wince.h \
    ../../../source/images/import_export/libtiff/tiffio.h \
    ../../../source/images/import_export/libtiff/tiffiop.h \
    ../../../source/images/import_export/libtiff/tiffvers.h \
    ../../../source/images/import_export/libtiff/uvcode.h


}

OTHER_FILES += \
    ../../../source/images/converter/yuy2_to_rgb.cl


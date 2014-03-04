#ifdef USE_LIB_TIFF
#include "libtiff/tiffio.h"
#endif
#include <fstream>
#include <string.h>
#include "images/error/module.h"
#include "string/module.h"
#include "tiff_importer.h"

PUNK_ENGINE_BEGIN
namespace Image
{
    struct PunkTiffHandle
    {
        std::istream* stream;
        Core::String filename;
    };

    TiffImporter::TiffImporter()
    {
    }

#ifdef USE_LIB_TIFF
    std::size_t PunkTIFFReadProc(thandle_t h, void* buffer, tmsize_t size)
    {
        PunkTiffHandle* handle = (PunkTiffHandle*)h;
        handle->stream->read((char*)buffer, size);
        return size;
        return 0;
    }

    tmsize_t PunkTIFFWriteProc(thandle_t, void*, tmsize_t)
    {
        return 0;
    }

    toff_t PunkTIFFSeekProc(thandle_t h, toff_t offset, int pos)
    {
        PunkTiffHandle* handle = (PunkTiffHandle*)h;
        handle->stream->seekg(offset, (std::ios_base::seekdir)pos);
        return offset;
        return 0;
    }

    int PunkTIFFCloseProc(thandle_t h)
    {
        PunkTiffHandle* handle = (PunkTiffHandle*)h;
        std::ifstream* s = dynamic_cast<std::ifstream*>(handle->stream);
        if (s)
            s->close();
        return 1;
        return 0;
    }

    toff_t PunkTIFFSizeProc(thandle_t h)
    {
        PunkTiffHandle* handle = (PunkTiffHandle*)h;
        auto pos = handle->stream->tellg();
        auto res = handle->stream->seekg(0, std::ios_base::end).tellg();
        handle->stream->seekg(pos, std::ios_base::beg);
        return res;
        return 0;
    }

    int PunkTIFFMapFileProc(thandle_t, void** base, toff_t* size)
    {
        return 0;
    }

    void PunkTIFFUnmapFileProc(thandle_t, void* base, toff_t size) {
    }

#endif

    bool TiffImporter::Load(const Core::String &filename)
    {
        std::ifstream stream((char*)filename.ToUtf8().Data(), std::ios_base::binary);
        if (!stream.is_open())
            throw Error::ImageException(L"File not found: " + filename);

        return Load(stream, this);
    }

    bool TiffImporter::Load(std::istream &stream, Image *image)
    {
#ifdef USE_LIB_TIFFF
        PunkTiffHandle h;
        h.stream = &stream;
        TIFF* tif;
        if (!(tif = TIFFClientOpen("", "r", &h, PunkTIFFReadProc,
                       PunkTIFFWriteProc, PunkTIFFSeekProc, PunkTIFFCloseProc, PunkTIFFSizeProc, PunkTIFFMapFileProc, PunkTIFFUnmapFileProc)))
        {
            return false;
        }

        uint32 width;
        uint32 height;
        uint32 bps;
        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);           // uint32 width;
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);        // uint32 height;
        TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);        // uint32 height;

        uint32 npixels = width * height;
        uint32* raster = (uint32*)_TIFFmalloc(npixels*sizeof(uint32));

        if (!TIFFReadRGBAImage(tif, width, height, raster, 0))
        {
            _TIFFfree(raster);
            return false;
        }

        image->Create(width, height, 4, ComponentType::UnsignedByte, ImageFormat::IMAGE_FORMAT_RGBA);
        memcpy(image->GetData(), raster, npixels*sizeof(uint32));

        _TIFFfree(raster);

        TIFFClose(tif);
        return true;
#else
        return false;
#endif
    }
}
PUNK_ENGINE_END


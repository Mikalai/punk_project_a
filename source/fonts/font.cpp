#include <string/module.h>
#include "font_error.h"
#include "font_builder.h"
#include "font.h"

PUNK_ENGINE_BEGIN
namespace Font {

    FontImpl::FontImpl(const Core::String& filepath) {

        FT_Error error = FT_New_Face((FT_Library)GetLibrary(), (char*)filepath.ToUtf8().Data(), 0, &m_face);

        if (error == FT_Err_Unknown_File_Format)
            throw Error::UnknownFileFormat(L"Unkown file format " + filepath);
        else if (error)
            throw Error::CantOpenFontFile(L"Can't open file " + filepath);

        error = FT_Set_Char_Size(m_face, 16*64, 16*64, 300, 300);
        if (error)
            throw Error::CantSetGlyphSize(L"Can't set glyph");
    }

    FontImpl::~FontImpl() {
        if (m_face) {
            FT_Done_Face(m_face);
            m_face = nullptr;
        }
    }

    void FontImpl::RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer) {
        CacheData* data = m_cache[m_size][symbol];
        if (!data)
            CacheSymbol(symbol);

        data = m_cache[m_size][symbol];
        *width = data->width;
        *height = data->height;
        *x_offset = data->x_offset;
        *y_offset = data->y_offset;
        *x_advance = data->x_advance;
        *y_advance = data->y_advance;
        *buffer = data->buffer;
    }

    void FontImpl::RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer) {
        CacheData* data = m_cache[m_size][symbol];
        if (!data)
            CacheSymbol(symbol);

        data = m_cache[m_size][symbol];
        *width = data->width;
        *height = data->height;
        *x_offset = data->x_offset;
        *y_offset = data->y_offset;
        *x_advance = data->x_advance;
        *y_advance = data->y_advance;
        *buffer = data->buffer;
    }

    void FontImpl::CacheSymbol(wchar_t s)
    {
        CacheData* data = m_cache[m_size][s];
        if (!data)
        {
            FT_UInt glyphIndex = FT_Get_Char_Index(m_face, s);
            FT_Error error = FT_Load_Glyph(m_face, glyphIndex, 0);
            if (error)
                throw Error::CantLoadGlyph(L"Can't load glypth");

            if (m_face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
            {
                error = FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_NORMAL);
                if (error)
                    throw Error::CantRenderGlyph(L"Can't render glyhp");
            }

            FT_GlyphSlot slot = m_face->glyph;

            data = new CacheData;
            data->width = slot->bitmap.width;
            data->height = slot->bitmap.rows;
            if (data->width*data->height > 0)
            {
                data->buffer = new unsigned char[data->width*data->height];
                memcpy(data->buffer, slot->bitmap.buffer, data->width*data->height);
            }
            data->x_offset = slot->bitmap_left;
            data->y_offset = slot->bitmap_top;
            data->x_advance = slot->advance.x >> 6;
            data->y_advance = slot->advance.y >> 6;

            m_cache[m_size][s] = data;
        }
    }

    void FontImpl::SetCharSize(int width, int height)
    {
        m_size = width * 1000 + height;
        FT_Error error = FT_Set_Char_Size(m_face, width*64, height*64, 96, 96);
        if (error)
            throw Error::CantSetGlyphSize(L"Can't set glypth size");
    }

    int FontImpl::CalculateLength(const Core::String& text) {
        int res = 0;
        for (int i = 0, max_i = text.Length(); i < max_i; ++i)
        {
            CacheData* data = m_cache[m_size][text[i]];

            if (!data)
                CacheSymbol(text[i]);

            data = m_cache[m_size][text[i]];
            if (res != 0)
                res += data->x_offset;
            res += data->x_advance;
        }
        return res;
    }

    int FontImpl::CalculateHeight(const Core::String& text) {
        int min_h = 0;
        int max_h = 0;
        for (int i = 0, max_i = text.Length(); i < max_i; ++i)
        {
            CacheData* data = m_cache[m_size][text[i]];

            if (!data)
                CacheSymbol(text[i]);

            data = m_cache[m_size][text[i]];
            if (max_h < data->y_offset)
                max_h = data->y_offset;
            if (min_h > data->y_offset - data->height)
                min_h = data->y_offset - data->height;
        }
        return max_h - min_h;
    }

    int FontImpl::GetHeight(wchar_t s) {
        CacheData* data = m_cache[m_size][s];
        if (!data)
            CacheSymbol(s);

        data = m_cache[m_size][s];
        return data->height + abs(data->y_offset);
    }
    int FontImpl::GetWidth(wchar_t s) {
        CacheData* data = m_cache[m_size][s];
        if (!data)
            CacheSymbol(s);

        data = m_cache[m_size][s];
        return data->x_advance ;
    }

    int FontImpl::GetMaxOffset(const Core::String& s) {
        int res = 0;
        for (int i = 0, max_i = s.Length(); i < max_i; ++i)
        {
            wchar_t c = s[i];
            int v = GetMaxOffset(c);
            if (res < v)
                res = v;
        }
        return res;
    }

    int FontImpl::GetMinOffset(const Core::String& s) {
        int res = 0;
        for (int i = 0, max_i = s.Length(); i < max_i; ++i)
        {
            wchar_t c = s[i];
            int v = GetMinOffset(c);
            if (res > v)
                res = v;
        }
        return res;
    }

    int FontImpl::GetMaxOffset(wchar_t s) {
        CacheData* data = m_cache[m_size][s];
        if (!data)
            CacheSymbol(s);

        data = m_cache[m_size][s];
        return data->y_offset ;
    }

    int FontImpl::GetMinOffset(wchar_t s) {
        CacheData* data = m_cache[m_size][s];
        if (!data)
            CacheSymbol(s);

        data = m_cache[m_size][s];
        return data->y_offset - data->height;
    }

    extern "C" PUNK_ENGINE_API IFont* CreateFont(const Core::String& filepath) {
        return new FontImpl(filepath);
    }

    extern "C" PUNK_ENGINE_API void DestroyFont(IFont* value) {
        FontImpl* impl = dynamic_cast<FontImpl*>(value);
        delete impl;
    }
}
PUNK_ENGINE_END

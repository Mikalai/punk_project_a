#include <map>

#ifdef USE_FREETYPE
#include <ft2build.h>
#include FT_FREETYPE_H
#endif //   USE_FREETYPE

#include <string/module.h>
#include <system/filesystem/binary_file.h>
#include <system/concurrency/module.h>
#include "font_builder.h"
#include "font_error.h"
#include "cache_data.h"

PUNK_ENGINE_BEGIN
namespace Font {

    Core::Rtti FontBuilder::Type {"Punk.Engine.Font.FontBuilder", typeid(FontBuilder).hash_code(), {&Core::Object::Type}};

    #ifdef USE_FREETYPE

    System::ThreadMutex g_library_mutex;
    FT_Library g_library;

    void* GetLibrary() {
        System::ThreadMutexLock lock(g_library_mutex);
        if (!g_library)
            FT_Init_FreeType(&g_library);
        return g_library;
    }

    void DestroyLibrary() {
        System::ThreadMutexLock lock(g_library_mutex);
        if (FT_Done_FreeType(g_library) != 0)
            throw Error::CantDestroyFontBuilder(L"Can't destroy font builder");

    }

    struct FontBuilderImpl
    {

        std::map<Core::String, FT_Face> fontFace;

        FT_Face curFace;
        int curSize;
        std::map<int, std::map<void*, std::map<char, CacheData*> > > cache;
        std::map<int, std::map<void*, std::map<wchar_t, CacheData*> > > wcache;        

        FontBuilderImpl(const Core::String& filename);
        ~FontBuilderImpl();
        void CacheSymbol(wchar_t symb);
        void Init(const Core::String& file);
        void Clear();
		void SetCurrentFace(const Core::String& fontName);
		void RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		void SetCharSize(int width, int height);
		void RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		int CalculateLength(const Core::String& text);
		int CalculateHeight(const Core::String& text);
		int GetHeight(wchar_t s);
		int GetWidth(wchar_t s);
		int GetMaxOffset(const Core::String& s);
		int GetMinOffset(const Core::String& s);
		int GetMaxOffset(wchar_t s);
		int GetMinOffset(wchar_t s);
    };

    FontBuilderImpl::FontBuilderImpl(const Core::String& fontfile)
    {
        Init(fontfile);
    }

    FontBuilderImpl::~FontBuilderImpl()
    {
        Clear();
    }

    void FontBuilderImpl::Clear()
    {
        DestroyLibrary();
    }

    void FontBuilderImpl::Init(const Core::String& fontfile)
	{
		Core::String iniFontsFile;
        Core::String pathToFonts = fontfile;

        iniFontsFile = pathToFonts + L"fonts.ini";

        Core::Buffer buffer;
        System::BinaryFile::Load(iniFontsFile, buffer);

		while(!buffer.IsEnd())
		{
			Core::String name = buffer.ReadWord();
			Core::String path = pathToFonts + buffer.ReadWord();

			FT_Face face;

            Core::Buffer buffer = path.ToUtf8();
            FT_Error error = FT_New_Face(g_library, (char*)buffer.Data(), 0, &face);

			if (error == FT_Err_Unknown_File_Format)
                throw Error::UnknownFileFormat(L"Unkown file format " + path);
			else if (error)
                throw Error::CantOpenFontFile(L"Can't open file " + path);

			error = FT_Set_Char_Size(face, 16*64, 16*64, 300, 300);

			if (error)
                throw Error::CantSetGlyphSize(L"Can't set glyph");

			curFace = face;
			fontFace[name] = face;
		}
	}

    void FontBuilderImpl::SetCurrentFace(const Core::String& fontName)
	{
		FT_Face f = fontFace[fontName];
		if (f != 0)
			curFace = f;
	}

    void FontBuilderImpl::SetCharSize(int width, int height)
	{
		curSize = width * 1000 + height;
		FT_Error error = FT_Set_Char_Size(curFace, width*64, height*64, 96, 96);
		if (error)
            throw Error::CantSetGlyphSize(L"Can't set glypth size");
	}

    void FontBuilderImpl::CacheSymbol(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
		{
			FT_UInt glyphIndex = FT_Get_Char_Index(curFace, s);
			FT_Error error = FT_Load_Glyph(curFace, glyphIndex, 0);
			if (error)
                throw Error::CantLoadGlyph(L"Can't load glypth");

			if (curFace->glyph->format != FT_GLYPH_FORMAT_BITMAP)
			{
				error = FT_Render_Glyph(curFace->glyph, FT_RENDER_MODE_NORMAL);
				if (error)
                    throw Error::CantRenderGlyph(L"Can't render glyhp");
			}

			FT_GlyphSlot slot = curFace->glyph;

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

			wcache[curSize][curFace][s] = data;
		}
	}

    int FontBuilderImpl::CalculateLength(const Core::String& text)
	{
        int res = 0;
        for (int i = 0, max_i = text.Length(); i < max_i; ++i)
		{
            CacheData* data = wcache[curSize][curFace][text[i]];

			if (!data)
                CacheSymbol(text[i]);

            data = wcache[curSize][curFace][text[i]];
			if (res != 0)
				res += data->x_offset;
			res += data->x_advance;
		}
		return res;
	}

    int FontBuilderImpl::CalculateHeight(const Core::String& text)
	{
        int min_h = 0;
        int max_h = 0;
        for (int i = 0, max_i = text.Length(); i < max_i; ++i)
		{
            CacheData* data = wcache[curSize][curFace][text[i]];

			if (!data)
                CacheSymbol(text[i]);

            data = wcache[curSize][curFace][text[i]];
			if (max_h < data->y_offset)
				max_h = data->y_offset;
			if (min_h > data->y_offset - data->height)
				min_h = data->y_offset - data->height;
		}
		return max_h - min_h;
	}

    int FontBuilderImpl::GetWidth(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);

		data = wcache[curSize][curFace][s];
		return data->x_advance ;
	}

    int FontBuilderImpl::GetHeight(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);

		data = wcache[curSize][curFace][s];
		return data->height + abs(data->y_offset);
	}

    int FontBuilderImpl::GetMaxOffset(const Core::String& s)
	{
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

    int FontBuilderImpl::GetMinOffset(const Core::String& s)
	{
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

    int FontBuilderImpl::GetMaxOffset(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);

		data = wcache[curSize][curFace][s];
		return data->y_offset ;
	}

    int FontBuilderImpl::GetMinOffset(wchar_t s)
	{
		CacheData* data = wcache[curSize][curFace][s];
		if (!data)
			CacheSymbol(s);

		data = wcache[curSize][curFace][s];
		return data->y_offset - data->height;
	}

    void FontBuilderImpl::RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer) {
		CacheData* data = cache[curSize][curFace][symbol];
        if (!data) {
			FT_UInt glyphIndex = FT_Get_Char_Index(curFace, symbol);
			FT_Error error = FT_Load_Glyph(curFace, glyphIndex, 0);
			if (error)
                throw Error::CantLoadGlyph("Error occured while loading a glyph");

            if (curFace->glyph->format != FT_GLYPH_FORMAT_BITMAP) {
				error = FT_Render_Glyph(curFace->glyph, FT_RENDER_MODE_NORMAL);
				if (error)
                    throw Error::CantRenderGlyph(L"Error occured while rendering a glyph");
			}

			FT_GlyphSlot slot = curFace->glyph;

			data = new CacheData;
			data->width = slot->bitmap.width;
			data->height = slot->bitmap.rows;
            if (data->width*data->height > 0) {
				data->buffer = new unsigned char[data->width*data->height];
				memcpy(data->buffer, slot->bitmap.buffer, data->width*data->height);
			}
			data->x_offset = slot->bitmap_left;
			data->y_offset = slot->bitmap_top;
			data->x_advance = slot->advance.x >> 6;
			data->y_advance = slot->advance.y >> 6;

			cache[curSize][curFace][symbol] = data;
		}

		data = cache[curSize][curFace][symbol];
		*width = data->width;
		*height = data->height;
		*x_offset = data->x_offset;
		*y_offset = data->y_offset;
		*x_advance = data->x_advance;
		*y_advance = data->y_advance;
		*buffer = data->buffer;
	}

    void FontBuilderImpl::RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
	{
		CacheData* data = wcache[curSize][curFace][symbol];
		if (!data)
			CacheSymbol(symbol);

		data = wcache[curSize][curFace][symbol];
		*width = data->width;
		*height = data->height;
		*x_offset = data->x_offset;
		*y_offset = data->y_offset;
		*x_advance = data->x_advance;
		*y_advance = data->y_advance;
		*buffer = data->buffer;
		//putchar('\n');/**/
	}
    #endif // USE_FREETYPE

    FontBuilder::FontBuilder(const Core::String& path)
	#ifdef USE_FREETYPE
    : impl(new FontBuilderImpl(path))
	#else
	: impl(nullptr)
	#endif // USE_FREETYPE
	{}

    FontBuilder::~FontBuilder()
    {
        #ifdef USE_FREETYPE
        delete impl;
        impl = nullptr;
        #endif // USE_FREETYPE
    }
	void FontBuilder::SetCurrentFace(const Core::String& fontName)
	{
	    #ifdef USE_FREETYPE
	    impl->SetCurrentFace(fontName);
	    #else
        (void)fontName;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	void FontBuilder::SetCharSize(int width, int height)
	{
        #ifdef USE_FREETYPE
	    impl->SetCharSize(width, height);
	    #else
        (void)width; (void)height;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::CalculateLength(const Core::String& text)
	{
        #ifdef USE_FREETYPE
        return impl->CalculateLength(text);
	    #else
        (void)text;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::CalculateHeight(const Core::String& text)
	{
        #ifdef USE_FREETYPE
        return impl->CalculateHeight(text);
	    #else
        (void)text;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetWidth(wchar_t s)
	{
        #ifdef USE_FREETYPE
        return impl->GetWidth(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetHeight(wchar_t s)
	{
        #ifdef USE_FREETYPE
        return impl->GetHeight(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetMaxOffset(const Core::String& s)
	{
        #ifdef USE_FREETYPE
        return impl->GetMaxOffset(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetMinOffset(const Core::String& s)
    {
        #ifdef USE_FREETYPE
        return impl->GetMinOffset(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetMaxOffset(wchar_t s)
	{
        #ifdef USE_FREETYPE
        return impl->GetMaxOffset(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	int FontBuilder::GetMinOffset(wchar_t s)
	{
        #ifdef USE_FREETYPE
        return impl->GetMinOffset(s);
	    #else
        (void)s;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	void FontBuilder::RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
	{
        #ifdef USE_FREETYPE
        return impl->RenderChar(symbol, width, height, x_offset, y_offset, x_advance, y_advance, buffer);
	    #else
        (void)symbol; (void)width; (void)height; (void)x_offset; (void)y_offset; (void)x_advance; (void)y_advance; (void)buffer;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

	void FontBuilder::RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer)
	{
        #ifdef USE_FREETYPE
        return impl->RenderChar(symbol, width, height, x_offset, y_offset, x_advance, y_advance, buffer);
	    #else
        (void)symbol; (void)width; (void)height; (void)x_offset; (void)y_offset; (void)x_advance; (void)y_advance; (void)buffer;
	    throw System::PunkException(L"Freetype is unavailable");
	    #endif // USE_FREETYPE
	}

    IFontBuilder* CreateFontBuilder(const Core::String& path) {
        return new FontBuilder(path);
    }

    void DestroyFontBuilder(IFontBuilder* value) {
        FontBuilder* v = dynamic_cast<FontBuilder*>(value);
        delete v;
    }
}
PUNK_ENGINE_END

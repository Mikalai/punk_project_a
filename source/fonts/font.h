#ifndef FONT_H
#define FONT_H

#include <config.h>
#include "ifont.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include "cache_data.h"

PUNK_ENGINE_BEGIN
namespace Font {
    class FontImpl : public IFont {
    public:
        FontImpl(const Core::String& filepath);
        virtual ~FontImpl();
        void RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer) override;
        void SetCharSize(int width, int height) override;
        void RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer) override;
        int CalculateLength(const Core::String& text) override;
        int CalculateHeight(const Core::String& text) override;
        int GetHeight(wchar_t s) override;
        int GetWidth(wchar_t s) override;
        int GetMaxOffset(const Core::String& s) override;
        int GetMinOffset(const Core::String& s) override;
        int GetMaxOffset(wchar_t s) override;
        int GetMinOffset(wchar_t s) override;
    private:
        void CacheSymbol(wchar_t s);

        FT_Face m_face;
        int m_size;
        std::map<int, std::map<int, CacheData*> > m_cache;
    };
}
PUNK_ENGINE_END

#endif // FONT_H

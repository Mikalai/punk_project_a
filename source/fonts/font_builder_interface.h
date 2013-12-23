#ifndef FONT_BUILDER_INTERFACE_H
#define FONT_BUILDER_INTERFACE_H

#include "config.h"

PUNK_ENGINE_BEGIN
namespace Font
{
    class IFontBuilder
    {
    public:
        virtual void SetCurrentFace(const Core::String& fontName) = 0;
        virtual void RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer) = 0;
        virtual void SetCharSize(int width, int height) = 0;
        virtual void RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer) = 0;
        virtual int CalculateLength(const Core::String& text) = 0;
        virtual int CalculateHeight(const Core::String& text) = 0;
        virtual int GetHeight(wchar_t s) = 0;
        virtual int GetWidth(wchar_t s) = 0;
        virtual int GetMaxOffset(const Core::String& s) = 0;
        virtual int GetMinOffset(const Core::String& s) = 0;
        virtual int GetMaxOffset(wchar_t s) = 0;
        virtual int GetMinOffset(wchar_t s) = 0;
    };

    extern "C" PUNK_ENGINE_API IFontBuilder* CreateFontBuilder(const Core::String& path);
    extern "C" PUNK_ENGINE_API void DestroyFontBuilder(IFontBuilder* value);
}
PUNK_ENGINE_END

#endif // FONT_BUILDER_INTERFACE_H

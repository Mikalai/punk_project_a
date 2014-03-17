#ifndef IFONT_H
#define IFONT_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Font {
    class IFont {
    public:
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

    extern "C" PUNK_ENGINE_API IFont* CreateFont(const Core::String& filepath);
    extern "C" PUNK_ENGINE_API void DestroyFont(IFont* value);
}
PUNK_ENGINE_END

#endif // IFONT_H

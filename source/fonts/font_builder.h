#ifndef _H_FONT_BUILDER
#define _H_FONT_BUILDER

#include "core/object.h"
#include "font_builder_interface.h"
#include <map>

PUNK_ENGINE_BEGIN
namespace Core { class String; }
namespace Font {

    struct FontBuilderImpl;

    class PUNK_ENGINE_LOCAL FontBuilder : public IFontBuilder, public Core::Object
	{
	public:
        FontBuilder(const Core::String& path);
		~FontBuilder();
		void Init();
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

    private:        
        FontBuilderImpl* impl;
        PUNK_OBJECT(FontBuilder)
	};
}
PUNK_ENGINE_END

#endif

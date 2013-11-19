#ifndef _H_FONT_BUILDER
#define _H_FONT_BUILDER

#include "system/core/object.h"
#include "font_builder_interface.h"
#include <map>

namespace System
{
	class string;
}

namespace Utility
{
    struct FontBuilderImpl;

    class PUNK_ENGINE_LOCAL FontBuilder : public IFontBuilder, public System::Object
	{
	public:
		FontBuilder();
		~FontBuilder();
		void Init();
		void SetCurrentFace(const System::string& fontName);
		void RenderChar(char symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		void SetCharSize(int width, int height);
		void RenderChar(wchar_t symbol, int* width, int* height, int* x_offset, int* y_offset, int* x_advance, int* y_advance, unsigned char** buffer);
		int CalculateLength(const System::string& text);
		int CalculateHeight(const System::string& text);
		int GetHeight(wchar_t s);
		int GetWidth(wchar_t s);
		int GetMaxOffset(const System::string& s);
		int GetMinOffset(const System::string& s);
		int GetMaxOffset(wchar_t s);
		int GetMinOffset(wchar_t s);

    private:        
        FontBuilderImpl* impl;
        PUNK_OBJECT(FontBuilder)
	};
}

#endif

#ifndef _H_WIDGET_STYLE
#define _H_WIDGET_STYLE

#include <map>
#include <config.h>
#include "picture.h"

PUNK_ENGINE_BEGIN
namespace Gui
{
    class AbstractPicture;
    class AbstractPictureFactory;

    struct Color
    {
        float r, g, b, a;
    };

	/**
	*	Holds data, that influence widgets visual representation.
	*	It has a set of colors and textures for different widget states:
	*	- Default state;
	*	- Mouse over widget;
	*	- Mouse clicked widget;
	*	- Widget focused;
	*/
    class Style
	{
    public:

        Style();
        ~Style();
        enum StylePart { BACK_COLOR = 0, BACK_COLOR_MOUSE_OVER = 1, BACK_COLOR_FOCUSED = 2, BACK_COLOR_MOUSE_PRESSED = 3 };

        AbstractPicture* GetBackTexture(StylePart part) const { return m_image[part]; }
        const Color& GetBackColor(StylePart part) const { return m_back_color[part]; }

        void EnableTextures(bool value) { m_use_textures = value; }
        bool IsEnabledTextures() const { return m_use_textures; }

        void SetBackColor(StylePart part, float r, float g, float b, float a) { m_back_color[part].r = r; m_back_color[part].g = g; m_back_color[part].b = b; m_back_color[part].a = a; }
        void SetFontColor(StylePart part, float r, float g, float b, float a) { m_font_color[part].r = r; m_font_color[part].g = g; m_font_color[part].b = b; m_back_color[part].a = a; }
        void SetBackTexture(StylePart part, AbstractPicture* value) { m_image[part] = value; }

        void SetType(const std::string& value) { m_type = value; }
        const std::string& GetType() const { return m_type; }

		void SetFont(const std::string& value) { m_font = value; }
        const std::string& GetFont() const { return m_font; }
		
		void SetCursor(AbstractPicturePtr value) { m_cursor = value; }
		const AbstractPicturePtr GetCursor() const { return m_cursor; }

    private:
		std::string m_font;
		AbstractPicturePtr m_cursor;
        std::string m_type;
        bool m_use_textures;
        Color m_back_color[4];
        Color m_font_color[4];
        AbstractPicture* m_image[4];
    };

    class StyleSet
    {
    public:
        ~StyleSet();
        static StyleSet* Create(const std::string& filename, AbstractPictureFactory* factory);
        Style* GetStyle(const std::string& type) { return m_style[type]; }
        void SetStyle(const std::string type, Style* value) { m_style[type] = value; }
        void SetName(const std::string& value) { m_name = value; }
        const std::string& GetName() const { return m_name; }        

    private:
        std::string m_name;        
        std::map<std::string, Style*> m_style;
    };
}
PUNK_ENGINE_END

#endif

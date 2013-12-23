#ifndef _H_ABSTRACT_RENDER
#define _H_ABSTRACT_RENDER

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Gui
{
	class AbstractFontManager;
	class AbstractPicture;
    struct Color;

	/**
	*	Abstract render that is used by widget render to draw gui elements.
	*/
    class AbstractRender
    {
    public:
        virtual ~AbstractRender() {}
        virtual void Translate(float dx, float dy) = 0;
        virtual void SetPosition(float x, float y) = 0;
        virtual void Rotate(float da) = 0;
        virtual void SetRotation(float a) = 0;        
        virtual void DrawPoint(float x, float y) = 0;
        virtual void DrawLine(float x1, float y1, float x2, float y2) = 0;
        virtual void DrawQuad(float x, float y, float width, float height) = 0;
		virtual void DrawTexturedQuad(float x, float y, float width, float height) = 0;
        virtual void DrawTextLine(float x, float y, const std::string& s) = 0;
        virtual void SetColor(float r, float g, float b) = 0;
        virtual void SetColor(const Color& value) = 0;
        virtual void SetAlpha(float a) = 0;
        virtual void SetFontManager(AbstractFontManager* value) = 0;
        virtual AbstractFontManager* GetFontManager() = 0;
        virtual void SetTexture(AbstractPicture* value) = 0;
        virtual void PushSate() = 0;
        virtual void PopState() = 0;
    };
}
PUNK_ENGINE_END

#endif	//	_H_ABSTRACT_RENDER


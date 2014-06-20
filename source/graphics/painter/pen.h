#ifndef _H_PUNK_GPU_PAINTER_PEN
#define _H_PUNK_GPU_PAINTER_PEN

#include <config.h>
#include <math/vec4.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	class PUNK_ENGINE_API Pen final
	{
	public:
		Pen();
		Pen(const Pen& pen);
		Pen& operator = (const Pen& pen);
		~Pen();

		void SetColor(const Math::vec4& color);
		void SetColor(float r, float g, float b, float a);
		void SetWidth(float value);

		const Math::vec4& GetColor() const;
		float GetWidth() const;

    private:
        float m_width {1};
        Math::vec4 m_color;
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_PAINTER_PEN

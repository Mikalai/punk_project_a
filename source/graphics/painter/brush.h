#ifndef _H_PUNK_GPU_BRUSH
#define _H_PUNK_GPU_BRUSH

#include <config.h>
#include <math/vec4.h>
#include <math/mat3.h>

PUNK_ENGINE_BEGIN

namespace Graphics
{
    class ITexture2D;

	class PUNK_ENGINE_API Brush final
	{
	public:
		Brush();
		Brush(const Brush& value);
		Brush& operator = (const Brush& value);
		~Brush();

		void SetColor(const Math::vec4& value);
		const Math::vec4& GetColor() const;
		void SetMatrix(const Math::mat3& value);
		const Math::mat3& GetMatrix() const;
		void SetStyle(int value);
		int GetStyle() const;
        void SetTexture(const ITexture2D* texture);
        const ITexture2D* GetTexture() const;

    private:
        Math::vec4 m_color;
        Math::mat3 m_transform;
        int m_style {0};
        const ITexture2D* m_texture {nullptr};
	};
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_GPU_BRUSH

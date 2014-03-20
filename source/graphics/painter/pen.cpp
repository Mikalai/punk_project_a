#include <algorithm>
#include "pen.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    void Pen::SetColor(const Math::vec4& color)
    {
        m_color = color;
    }

    void Pen::SetColor(float r, float g, float b, float a)
    {
        m_color.Set(r, g, b, a);
    }

    void Pen::SetWidth(float value)
    {
        m_width = value;
    }

    const Math::vec4& Pen::GetColor() const
    {
        return m_color;
    }

    float Pen::GetWidth() const
    {
        return m_width;
    }
    Pen::Pen()
    {}

}
PUNK_ENGINE_END

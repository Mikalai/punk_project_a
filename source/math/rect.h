#ifndef _H_PUNK_MATH_RECT
#define _H_PUNK_MATH_RECT

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math {

    template<class T>
    class RectangleTemplate	{
	public:
        RectangleTemplate()
            : m_x(0)
            , m_y(0)
            , m_width(1)
            , m_height(1)
        {}

        RectangleTemplate(T x, T y, T width, T height)
            : m_x(x)
            , m_y(y)
            , m_width(width)
            , m_height(height)
        {}

        RectangleTemplate(const Math::vec2& left_top_cornder, const Math::vec2 dimension)
            : m_x(left_top_cornder.X())
            , m_y(left_top_cornder.Y())
            , m_width(dimension.X())
            , m_height(dimension.Y())
        {}

        RectangleTemplate(const Math::vec4& rect)
            : m_x(rect.X())
            , m_y(rect.Y())
            , m_width(rect.Z())
            , m_height(rect.W())
        {}

        T GetX() const {
            return m_x;
        }

        T GetY() const {
            return m_y;
        }

        T GetWidth() const {
            return m_width;
        }

        T GetHeight() const {
            return m_height;
        }

        void Set(T x, T y, T width, T height)
        {
            m_x = x;
            m_y = y;
            m_width = width;
            m_height = height;
        }
		
	private:

        T m_x;
        T m_y;
        T m_width;
        T m_height;
	};

    using Rectangle = RectangleTemplate<float>;

};
PUNK_ENGINE_END

#endif	//	_H_PUNK_MATH_RECT

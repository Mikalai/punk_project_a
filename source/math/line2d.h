#ifndef _H_PUNK_MATH_LINE_2D
#define _H_PUNK_MATH_LINE_2D

#include "config.h"
#include "vec2.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            enum class Relation;

            class PUNK_ENGINE_API Line2D
            {
            public:
                Line2D();
                Line2D(const vec2& org, const vec2& dest);
                Line2D(const Line2D& line);
                Line2D& Rotate();
                Line2D& Flip();
                const vec2 Direction() const;
                float SegmentLength() const;
                const vec2& Origin() const;
                vec2& Origin();
                const vec2& Destination() const;
                vec2& Destination();
                const vec2 Point(float t);
            private:
                vec2 m_origin;
                vec2 m_destination;
            };

            PUNK_ENGINE_API Relation CrossLine(const Line2D& a, const Line2D& b, float& t);
            PUNK_ENGINE_API float Distance(const vec2& p, const Line2D& line);
        }
    }
}

#endif

#ifndef _H_PUNK_MATH_VEC2_MATH
#define _H_PUNK_MATH_VEC2_MATH

#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Core {
            class String;
        }

        namespace Math {

            enum class Relation;

            class PUNK_ENGINE_API vec2 {
            public:
                const float& X() const;
                float& X();
                float& Y();
                const float& Y() const;
                float& R();
                const float& R() const;
                const float& G() const;
                float& G();
                vec2 XY() const;
                operator float* ();
                float& operator [] (int i);
                const float& operator [] (int i) const;
                vec2& operator = (const vec2& vec);
                vec2();
                vec2(float x, float y);
                vec2(const vec2& vec);
                vec2(const vec2& origin, const vec2& destination);
                vec2& Normalize();
                float Length();
                float SqrLength();
                vec2& Negate();
                vec2& Set(float x, float y);
                vec2 ComponentMult(const vec2& v);
                float Dot(const vec2& vec);
                const Core::String ToString() const;
            private:
                static const int Size_c = 2;
                float m_v[Size_c];
            };

            PUNK_ENGINE_API const vec2 operator + (const vec2& v1, const vec2& v2);
            PUNK_ENGINE_API const vec2 operator - (const vec2& v1, const vec2& v2);
            PUNK_ENGINE_API const vec2 operator *(const vec2& m_v, float d);
            PUNK_ENGINE_API const vec2 operator *(float d, const vec2 &m_v);
            PUNK_ENGINE_API const vec2 operator / (const vec2& m_v, float d);
            PUNK_ENGINE_API bool operator == (const vec2& a, const vec2& b);
            PUNK_ENGINE_API bool operator != (const vec2& a, const vec2& b);

            class PUNK_ENGINE_API ivec2 {
            public:
                ivec2();
                ivec2(int x, int y);
                ivec2(const ivec2& vec);
                ivec2(const ivec2& origin, const ivec2& destination);
                ivec2& operator = (const ivec2& vec);
                const int& X() const;
                int& X();
                int& Y();
                const int& Y() const;
                int& R();
                const int& R() const;
                const int& G() const;
                int& G();
                ivec2 XY() const;
                operator int* ();
                int& operator [] (int i);
                const int& operator [] (int i) const;
                int SqrLength();
                ivec2& Negate();
                ivec2& Set(int x, int y);
                ivec2 ComponentMult(const ivec2& v);
                int Dot(const ivec2& vec);
                const Core::String ToString() const;
            private:
                static const int Size_c = 2;
                int m_v[Size_c];
            };

            PUNK_ENGINE_API const ivec2 operator + (const ivec2& v1, const ivec2& v2);
            PUNK_ENGINE_API const ivec2 operator - (const ivec2& v1, const ivec2& v2);
            PUNK_ENGINE_API const ivec2 operator *(const ivec2& m_v, int d);
            PUNK_ENGINE_API const ivec2 operator *(int d, const ivec2 &m_v);
            PUNK_ENGINE_API const ivec2 operator / (const ivec2& m_v, int d);
            PUNK_ENGINE_API bool operator == (const ivec2& a, const ivec2& b);
            PUNK_ENGINE_API bool operator != (const ivec2& a, const ivec2& b);
        }
    }
}

#endif  //  _H_PUNK_MATH_VEC2_MATH

#ifndef _H_VEC3_MATH1
#define _H_VEC3_MATH1

#include <initializer_list>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Core {
            class String;
        }

        namespace Math {

            class vec2;

            class PUNK_ENGINE_API vec3 {
            public:
                vec3();
                vec3(const std::initializer_list<float>& v);                
                vec3(float x, float y, float z);
                vec3(const vec3& vec);
                vec3(const vec3& origin, const vec3& destination);
                static const vec3 Null();
                const float& X() const;
                float& X();
                const float& Y() const;
                float& Y();
                const float& Z() const;
                float& Z();
                const vec3 Negated() const;
                vec3& Negate();
                float Length() const;
                const vec3 Normalized() const;
                vec3& Normalize();
                const vec3 Cross(const vec3& vec) const;
                vec3& Chop(float eps = float(0.00001));
                const vec3 ComponentMult(const vec3& v) const;
                const vec2 XY() const;
                const vec2 YX() const;
                const vec2 XZ() const;
                const vec2 ZX() const;
                const vec2 YZ() const;
                const vec2 ZY() const;
                const vec3 XYZ() const;
                const vec3 XZY() const;
                const vec3 YXZ() const;
                const vec3 YZX() const;
                const vec3 ZXY() const;
                const vec3 ZYX() const;
                vec3& Nullify();
                vec3& operator += (const vec3& vec);
                vec3& operator -= (const vec3& vec);
                vec3& operator *= (float value);
                vec3& operator /= (float value);
                float& operator [] (int i);
                const float& operator [] (int i) const;
                float SquareLength() const;
                void Set(float x, float y, float z);
                float Dot(const vec3& a) const;
                vec3& operator = (const vec3& vec);
                const vec3 operator -() const;
                Core::String ToString() const;
            private:
                static const int Size_c = 3;
                float m_v[Size_c];
            };

            PUNK_ENGINE_API const vec3 operator + (const vec3& a, const vec3& b);
            PUNK_ENGINE_API const vec3 operator -(const vec3& a, const vec3& b);
            PUNK_ENGINE_API const vec3 operator *(const vec3& a, float d);
            PUNK_ENGINE_API const vec3 operator *(float d, const vec3& a);
            PUNK_ENGINE_API const vec3 operator *(const vec3& a, const vec3& b);
            PUNK_ENGINE_API const vec3 operator /(const vec3& a, float d);
            PUNK_ENGINE_API bool operator ==(const vec3& a, const vec3& b);
            PUNK_ENGINE_API bool operator !=(const vec3& a, const vec3& b);

            class PUNK_ENGINE_API ivec3
            {
            public:
                ivec3();
                ivec3(int x, int y, int z);
                ivec3(const ivec3& vec);
                const int& X() const;
                int& X();
                const int& Y() const;
                int& Y();
                const int& Z() const;
                int& Z();
                int & operator [] (int i);
                const int& operator [] (int i) const;
                void Set(int x, int y, int z);
            private:
                static const int Size_c = 3;
                int m_v[Size_c];
            };
        }
    }
}
#endif

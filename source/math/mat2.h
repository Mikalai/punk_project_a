/****************************************************
*	File: mat2.h
*    Author: Mikalai Abramau
*	Desc: Class implemeting 2x2 matrix
****************************************************/

#ifndef _H_PUNK_MATH_MAT2X2_MATH
#define _H_PUNK_MATH_MAT2X2_MATH

#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            class vec2;

            class PUNK_ENGINE_API mat2
            {
            protected:
                float m[4];
            public:

                static const mat2 CreateIdentity();
                static const mat2 CreateMirrorX();
                static const mat2 CreateMirrorY();
                static const mat2 CreateMirrorXY();
                mat2();
                mat2(float a1, float a2, float a3, float a4);
                mat2& operator = (const mat2& v);
                const float& operator [] (int i) const;
                float& operator [] (int i);
                const vec2 Row(int i);
                const vec2 Column(int i);
                float Determinant() const;
                operator float* ();
                operator const float* () const;
                mat2& Inverse();
                const mat2 Inversed() const;
                mat2& SetColumn(int column, const vec2& v);
                mat2& SetRow(int row, const vec2& v);
                mat2& Identity();
                mat2& operator *= (float k);
            };

            PUNK_ENGINE_API const mat2 operator * (const mat2& a, const mat2& b);
            PUNK_ENGINE_API const vec2 operator * (const mat2& a, const vec2& v);
            PUNK_ENGINE_API const mat2 operator * (const mat2& a, float b);
            PUNK_ENGINE_API const mat2 operator * (float b, const mat2& a);
            PUNK_ENGINE_API const mat2 operator / (const mat2& a, float b);
            PUNK_ENGINE_API const mat2 operator + (const mat2& a, const mat2& b);
            PUNK_ENGINE_API const mat2 operator - (const mat2& l, const mat2& r);
            PUNK_ENGINE_API bool operator == (const mat2& l, const mat2& r);
        }
    }
}

#endif  //  _H_PUNK_MATH_MAT2X2_MATH

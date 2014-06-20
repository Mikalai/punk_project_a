#include <memory.h>
#include <cmath>
#include <limits>
#include <string/string.h>
#include "quat.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

namespace Punk {
    namespace Engine {
        namespace Math
        {
            mat4::mat4()
				: m{ { 1, 0, 0, 0
				, 0, 1, 0, 0
				, 0, 0, 1, 0
				, 0, 0, 0, 1 } } {}

            mat4::mat4(float a0, float a1, float a2, float a3,
                 float a4, float a5, float a6, float a7,
                 float a8, float a9, float a10, float a11,
                 float a12, float a13, float a14, float a15)
				 : m{ { a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15 } } {}

            mat4::mat4(std::initializer_list<float> v) {
                auto it = v.begin();
                for (int i = 0; i < 16; ++i) {
                    m[i] = *(it++);
                }
            }

            mat4::mat4(const mat4& mm) {
				m = mm.m;
            }

            float& mat4::operator [] (int i) {
                return m[i];
            }

            const float& mat4::operator [] (int i) const {
                return m[i];
            }

            const vec4 mat4::GetRow(int row) const {
                return vec4(m[0 * 4 + row],
                        m[1 * 4 + row],
                        m[2 * 4 + row],
                        m[3 * 4 + row]);
            }

            void mat4::SetColumn(int column, const vec4& v) {
                for (int i = 0; i < 4; i++) {
                    m[column * 4 + i] = v[i];
                }
            }

            mat4& mat4::operator *= (const mat4& b) {
                mat4 a = *this;

                SetColumn(0, vec4(
                              b[0] * a[0] + b[1] * a[4] + b[2] * a[8] + b[3] * a[12],
                        b[0] * a[1] + b[1] * a[5] + b[2] * a[9] + b[3] * a[13],
                        b[0] * a[2] + b[1] * a[6] + b[2] * a[10] + b[3] * a[14],
                        b[0] * a[3] + b[1] * a[7] + b[2] * a[11] + b[3] * a[15]));
                SetColumn(1, vec4(
                              b[4] * a[0] + b[5] * a[4] + b[6] * a[8] + b[7] * a[12],
                        b[4] * a[1] + b[5] * a[5] + b[6] * a[9] + b[7] * a[13],
                        b[4] * a[2] + b[5] * a[6] + b[6] * a[10] + b[7] * a[14],
                        b[4] * a[3] + b[5] * a[7] + b[6] * a[11] + b[7] * a[15]));
                SetColumn(2, vec4(
                              b[8] * a[0] + b[9] * a[4] + b[10] * a[8] + b[11] * a[12],
                        b[8] * a[1] + b[9] * a[5] + b[10] * a[9] + b[11] * a[13],
                        b[8] * a[2] + b[9] * a[6] + b[10] * a[10] + b[11] * a[14],
                        b[8] * a[3] + b[9] * a[7] + b[10] * a[11] + b[11] * a[15]));
                SetColumn(3, vec4(
                              b[12] * a[0] + b[13] * a[4] + b[14] * a[8] + b[15] * a[12],
                        b[12] * a[1] + b[13] * a[5] + b[14] * a[9] + b[15] * a[13],
                        b[12] * a[2] + b[13] * a[6] + b[14] * a[10] + b[15] * a[14],
                        b[12] * a[3] + b[13] * a[7] + b[14] * a[11] + b[15] * a[15]));

                return *this;
            }

            const mat4 mat4::Inversed() const
            {
#define SWAP_ROWS(a, b) {  float * _tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c)     m [r*4+c]

                float	wtmp [4][8];
                float	m0, m1, m2, m3, s;
                float	* r0, * r1, * r2, * r3;

                r0 = wtmp [0];
                r1 = wtmp [1];
                r2 = wtmp [2];
                r3 = wtmp [3];

                r0 [0] = MAT(m,0,0);
                r0 [1] = MAT(m,0,1);
                r0 [2] = MAT(m,0,2);
                r0 [3] = MAT(m,0,3);
                r0 [4] = 1;
                r0 [5] =
                        r0 [6] =
                        r0 [7] = 0;

                r1 [0] = MAT(m,1,0);
                r1 [1] = MAT(m,1,1);
                r1 [2] = MAT(m,1,2);
                r1 [3] = MAT(m,1,3);
                r1 [5] = 1;
                r1 [4] =
                        r1 [6] =
                        r1 [7] = 0,

                        r2 [0] = MAT(m,2,0);
                r2 [1] = MAT(m,2,1);
                r2 [2] = MAT(m,2,2);
                r2 [3] = MAT(m,2,3);
                r2 [6] = 1;
                r2 [4] =
                        r2 [5] =
                        r2 [7] = 0;

                r3 [0] = MAT(m,3,0);
                r3 [1] = MAT(m,3,1);
                r3 [2] = MAT(m,3,2);
                r3 [3] = MAT(m,3,3);
                r3 [7] = 1;
                r3 [4] =
                        r3 [5] =
                        r3 [6] = 0;

                // choose pivot - or die
                if ( fabs (r3 [0] )> fabs ( r2 [0] ) )
                    SWAP_ROWS ( r3, r2 );

                if ( fabs ( r2 [0] ) > fabs ( r1 [0] ) )
                    SWAP_ROWS ( r2, r1 );

                if ( fabs ( r1 [0] ) > fabs ( r0 [0 ] ) )
                    SWAP_ROWS ( r1, r0 );

                if ( r0 [0] == 0 )
                    return mat4();

                // eliminate first variable
                m1 = r1[0]/r0[0];
                m2 = r2[0]/r0[0];
                m3 = r3[0]/r0[0];

                s = r0[1];
                r1[1] -= m1 * s;
                r2[1] -= m2 * s;
                r3[1] -= m3 * s;

                s = r0[2];
                r1[2] -= m1 * s;
                r2[2] -= m2 * s;
                r3[2] -= m3 * s;

                s = r0[3];
                r1[3] -= m1 * s;
                r2[3] -= m2 * s;
                r3[3] -= m3 * s;

                s = r0[4];

                if ( s != 0 )
                {
                    r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s;
                }

                s = r0[5];

                if ( s != 0.0 )
                {
                    r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s;
                }

                s = r0[6];

                if ( s != 0 )
                {
                    r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s;
                }

                s = r0[7];

                if ( s != 0 )
                {
                    r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s;
                }

                // choose pivot - or die
                if ( fabs (r3 [1] ) > fabs ( r2 [1] ) )
                    SWAP_ROWS ( r3, r2 );

                if ( fabs ( r2 [1] ) > fabs ( r1 [1] ) )
                    SWAP_ROWS ( r2, r1 );

                if ( r1 [1] == 0 )
                    return mat4();


                // eliminate second variable
                m2     = r2[1]/r1[1]; m3     = r3[1]/r1[1];
                r2[2] -= m2 * r1[2];  r3[2] -= m3 * r1[2];
                r2[3] -= m2 * r1[3];  r3[3] -= m3 * r1[3];

                s = r1[4];

                if ( 0 != s )
                {
                    r2[4] -= m2 * s; r3[4] -= m3 * s;
                }

                s = r1[5];

                if ( 0 != s )
                {
                    r2[5] -= m2 * s; r3[5] -= m3 * s;
                }

                s = r1[6];

                if ( 0 != s )
                {
                    r2[6] -= m2 * s; r3[6] -= m3 * s;
                }

                s = r1[7];

                if ( 0 != s )
                {
                    r2[7] -= m2 * s; r3[7] -= m3 * s;
                }

                // choose pivot - or die
                if ( fabs ( r3 [2] ) > fabs ( r2 [2] ) )
                    SWAP_ROWS ( r3, r2 );

                if ( r2 [2] == 0)
                    return mat4();

                // eliminate third variable
                m3     = r3[2]/r2[2];
                r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
                        r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
                        r3[7] -= m3 * r2[7];

                // last check
                if ( r3 [3] == 0 )
                    return mat4();


                // now back substitute row 3
                s      = 1.0f/r3[3];
                r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

                // now back substitute row 2
                m2    = r2[3];
                s     = 1.0f/r2[2];
                r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
                        r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
                m1     = r1[3];
                r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
                        r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;

                m0     = r0[3];
                r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
                        r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

                // now back substitute row 1
                m1    = r1[2];
                s     = 1.0f/r1[1];
                r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
                        r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);

                m0     = r0[2];
                r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
                        r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

                // now back substitute row 0
                m0    = r0[1];
                s     = 1.0f/r0[0];
                r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
                        r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

                mat4 res;
                float* out = res.m.data();
                MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5];
                MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7];
                MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5];
                MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7];
                MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5];
                MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7];
                MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5];
                MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7];

#undef MAT
#undef SWAP_ROWS

                return res;
            }

            //  mult matrix

            const mat4 operator + (const mat4& a, const mat4& b)
            {
                mat4 c;
                for (int i = 0; i < 16; i++)
                {
                    c[i] = a[i] + b[i];
                }
                return c;
            }

            //  mult matrix

            const mat4 operator * (const mat4& a, const mat4& b)
            {
                mat4 c;
                c.SetColumn(0, vec4(
                                b[0] * a[0] + b[1] * a[4] + b[2] * a[8] + b[3] * a[12],
                        b[0] * a[1] + b[1] * a[5] + b[2] * a[9] + b[3] * a[13],
                        b[0] * a[2] + b[1] * a[6] + b[2] * a[10] + b[3] * a[14],
                        b[0] * a[3] + b[1] * a[7] + b[2] * a[11] + b[3] * a[15]));
                c.SetColumn(1, vec4(
                                b[4] * a[0] + b[5] * a[4] + b[6] * a[8] + b[7] * a[12],
                        b[4] * a[1] + b[5] * a[5] + b[6] * a[9] + b[7] * a[13],
                        b[4] * a[2] + b[5] * a[6] + b[6] * a[10] + b[7] * a[14],
                        b[4] * a[3] + b[5] * a[7] + b[6] * a[11] + b[7] * a[15]));
                c.SetColumn(2, vec4(
                                b[8] * a[0] + b[9] * a[4] + b[10] * a[8] + b[11] * a[12],
                        b[8] * a[1] + b[9] * a[5] + b[10] * a[9] + b[11] * a[13],
                        b[8] * a[2] + b[9] * a[6] + b[10] * a[10] + b[11] * a[14],
                        b[8] * a[3] + b[9] * a[7] + b[10] * a[11] + b[11] * a[15]));
                c.SetColumn(3, vec4(
                                b[12] * a[0] + b[13] * a[4] + b[14] * a[8] + b[15] * a[12],
                        b[12] * a[1] + b[13] * a[5] + b[14] * a[9] + b[15] * a[13],
                        b[12] * a[2] + b[13] * a[6] + b[14] * a[10] + b[15] * a[14],
                        b[12] * a[3] + b[13] * a[7] + b[14] * a[11] + b[15] * a[15]));
                return c;
            }


            const vec4 operator * (const mat4& m, const vec4& v)
            {
                return vec4(
                            m[0]*v[0] + m[4]*v[1] + m[8]*v[2] + m[12]*v[3],
                        m[1]*v[0] + m[5]*v[1] + m[9]*v[2] + m[13]*v[3],
                        m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3],
                        m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3]);
            }


            const vec3 operator * (const mat4& m, const vec3& v)
            {
                auto r = m * vec4(v[0], v[1], v[2], float(1));
                return vec3(r[0] / r[3], r[1] / r[3], r[2] / r[3]);
            }


            const mat4 operator * (const mat4& m, const float& v)
            {
                Math::mat4 res;
                for (int i = 0; i < 16; i++)
                    res[i] = m[i]*v;
                return res;
            }


            const mat4 operator * (const float& v, const mat4& m)
            {
                Math::mat4 res;
                for (int i = 0; i < 16; i++)
                    res[i] = m[i]*v;
                return res;
            }



            const mat4 mat4::Transposed() const
            {
                mat4 res;
                res.SetColumn(0, vec4(m[0], m[4], m[8], m[12]));
                res.SetColumn(1, vec4(m[1], m[5], m[9], m[13]));
                res.SetColumn(2, vec4(m[2], m[6], m[10], m[14]));
                res.SetColumn(3, vec4(m[3], m[7], m[11], m[15]));

                return res;
            }

            const vec3 mat4::TranslationPart() const
            {
                return vec3(m[12], m[13], m[14]);
            }

            const mat3 mat4::RotationPart() const
            {
                mat3 res;
                res.SetColumn(0, vec3(m[0], m[1], m[2]));
                res.SetColumn(1, vec3(m[4], m[5], m[6]));
                res.SetColumn(2, vec3(m[8], m[9], m[10]));
                return res;
            }

            const mat4 mat4::RotationPart4x4() const
            {
                mat4 res;
                res.SetColumn(0, vec4(m[0], m[1], m[2], 0));
                res.SetColumn(1, vec4(m[4], m[5], m[6], 0));
                res.SetColumn(2, vec4(m[8], m[9], m[10], 0));
                res.SetColumn(3, vec4(0, 0, 0, 1));
                return res;
            }

            const Core::String mat4::ToString() const
            {
                return Core::String(L"{0} {1} {2} {3}\n {4} {5} {6} {7} \n {8} {9} {10} {11}\n {12} {13} {14} {15}\n").
                        arg(m[0]).arg(m[4]).arg(m[8]).arg(m[12]).
                        arg(m[1]).arg(m[5]).arg(m[9]).arg(m[13]).
                        arg(m[2]).arg(m[6]).arg(m[10]).arg(m[14]).
                        arg(m[3]).arg(m[7]).arg(m[11]).arg(m[15]);
            }

            bool operator == (const mat4& l, const mat4& r) {
                for (int i = 0; i < 16; ++i) {
                    if (fabs(l[i] - r[i]) > std::numeric_limits<float>::epsilon())
                        return false;
                }
                return true;
            }

            bool operator != (const mat4& l, const mat4& r) {
                return !(l == r);
            }

        }
    }
}

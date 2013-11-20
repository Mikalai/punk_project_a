#include <memory.h>
#include <math.h>
#include <limits>
#include "math_error.h"
#include "vec2.h"
#include "mat2.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            const mat2 mat2::CreateIdentity() {
                return mat2();
            }

            const mat2 mat2::CreateMirrorX() {
                mat2 m;
                m[0] = 1;
                m[1] = 0;
                m[2] = 0;
                m[3] = -1;
                return m;
            }

            const mat2 mat2::CreateMirrorY() {
                mat2 m;
                m[0] = -1;
                m[1] = 0;
                m[2] = 0;
                m[3] = 1;
                return m;
            }

            const mat2 mat2::CreateMirrorXY() {
                mat2 m;
                m[0] = -1;
                m[1] = 0;
                m[2] = 0;
                m[3] = -1;
                return m;
            }

            mat2::mat2() {
                memset(m, 0, sizeof(m));
                m[0] = m[3] = 1.0f;
            }

            mat2::mat2(float a1, float a2, float a3, float a4) {
                m[0] = a1;
                m[1] = a2;
                m[2] = a3;
                m[3] = a4;
            }

            mat2& mat2::operator = (const mat2& v)
            {
#ifdef _WIN32
                memcpy_s(m, sizeof(m), v.m, sizeof(m));
#elif defined __gnu_linux__
                memcpy(m, v.m, sizeof(m));
#endif
                return *this;
            }

            const float& mat2::operator [] (int i) const {
                if (i < 0 || i > 3)
                    throw Error::IndexOutOfRange(i);
                return m[i];
            }

            float& mat2::operator [] (int i) {
                if (i < 0 || i > 3)
                    throw Error::IndexOutOfRange(i);
                return m[i];
            }

            const vec2 mat2::Row(int row) {
                return vec2(m[row], m[2 + row]);
            }

            const vec2 mat2::Column(int col) {
                return vec2(m[0 + 2*col], m[1 + 2*col]);
            }

            float mat2::Determinant() const {
                return m[0] * m[3] - m[1] * m[2];
            }

            mat2::operator float* () {
                return m;
            }

            mat2::operator const float* () const {
                return m;
            }

            mat2& mat2::Inverse() {
                float d = Determinant();
                if (d == float(0))
                    throw Error::MatrixInverseFailed(0);

                d = float(1) / d;
                float tm[4];
                tm[0] =	 m[3] * d;
                tm[1] = -m[1] * d;
                tm[2] = -m[2] * d;
                tm[3] =  m[0] * d;
                memcpy(m, tm, sizeof(m));
                return *this;
            }

            const mat2 mat2::Inversed() const {
                float d = Determinant();
                if (d == float(0))
                    throw Error::MatrixInverseFailed(0);

                d = float(1) / d;

                mat2 tm;
                tm[0] =	 m[3] * d;
                tm[1] = -m[1] * d;
                tm[2] = -m[2] * d;
                tm[3] =  m[0] * d;

                return tm;
            }

            mat2& mat2::SetColumn(int column, const vec2& v) {
                for (int i = 0; i < 2; i++) {
                    m[column * 2 + i] = v[i];
                }
                return *this;
            }

            mat2& mat2::SetRow(int row, const vec2& v) {
                for (int i = 0; i < 2; i++) {
                    m[i * 2 + row] = v[i];
                }
                return *this;
            }

            mat2& mat2::Identity() {
                float tm[4] = {float(1),float(0),float(0),float(1)};
                memcpy(m, tm, sizeof(m));
                return *this;
            }

            mat2& mat2::operator *= (float k) {
                for (int i = 0; i != 4; ++i) {
                    m[i] *= k;
                }
                return *this;
            }

            const mat2 operator *(const mat2& a, const mat2& b) {
                mat2 c;
                c.SetRow(0, vec2(a[0]*b[0] + a[2]*b[1], a[0]*b[2] + a[2]*b[3]));
                c.SetRow(1, vec2(a[1]*b[0] + a[3]*b[1], a[1]*b[2] + a[3]*b[3]));
                return c;
            }

            const vec2 operator * (const mat2& a, const vec2& v) {
                vec2 r;
                r[0] = a[0]*v[0] + a[2]*v[1];
                r[1] = a[1]*v[0] + a[3]*v[1];
                return r;
            }

            const mat2 operator * (const mat2& a, float b) {
                mat2 c(a);
                c[0] *= b;
                c[1] *= b;
                c[2] *= b;
                c[3] *= b;
                return c;
            }

            const mat2 operator * (float b, const mat2& a) {
                mat2 c(a);
                c[0] *= b;
                c[1] *= b;
                c[2] *= b;
                c[3] *= b;
                return c;
            }

            const mat2 operator / (const mat2& a, float b) {
                if (b == float(0))
                    throw Error::DevisionByZero(0);

                b = float(1) / b;
                return a * b;
            }

            const mat2 operator + (const mat2& a, const mat2& b) {
                mat2 m;
                for (int i = 0; i < 4; i++)
                    m[i] = a[i] + b[i];
                return m;
            }

            const mat2 operator - (const mat2& l, const mat2& r) {
                mat2 m;
                for (int i = 0; i < 4; i++)
                    m[i] = l[i] - r[i];
                return m;
            }

            bool operator == (const mat2& l, const mat2& r) {
                for (int i = 0; i < 4; ++i) {
                    float f = fabs(l[i] - r[i]);
                    if (f > std::numeric_limits<float>::epsilon())
                        return false;
                }
                return true;
            }
        }
    }
}

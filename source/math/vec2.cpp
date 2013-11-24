#include <math.h>
#include <memory.h>
#include "relations.h"
#include "string/string.h"
#include "vec2.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            const float& vec2::X() const {
                return m_v[0];
            }

            float& vec2::X() {
                return m_v[0];
            }

            float& vec2::Y() {
                return m_v[1];
            }

            const float& vec2::Y() const {
                return m_v[1];
            }

            const vec2 vec2::XY() const {
                return vec2(m_v[0], m_v[1]);
            }

            const vec2 vec2::YX() const {
                return vec2{m_v[1], m_v[0]};
            }

            vec2::operator float* () {
                return &m_v[0];
            }

            float& vec2::operator [] (int i) {
                return m_v[i];
            }

            const float& vec2::operator [] (int i) const {
                return m_v[i];
            }

            const vec2 vec2::operator -()
            {
                return Negated();
            }

            vec2& vec2::operator = (const vec2& vec) {
#ifdef _WIN32
                memcpy_s(m_v, sizeof(m_v), vec.m_v, sizeof(m_v));
#elif defined __gnu_linux__
                memcpy(m_v, vec.m_v, sizeof(m_v));
#endif
                return *this;
            }

            vec2::vec2() {
                memset(m_v, 0, sizeof(m_v));
            }

            vec2::vec2(std::initializer_list<float> v) {
                int index = 0;
                for (auto c : v) {
                    m_v[index] = c;
                    if (++index == 2)
                        break;
                }
            }

            vec2::vec2(float x, float y) {
                m_v[0] = x; m_v[1] = y;
            }

            vec2::vec2(const vec2& vec) {
#ifdef _WIN32
                memcpy_s(m_v, sizeof(m_v), vec.m_v, sizeof(m_v));
#elif defined __gnu_linux__
                memcpy(m_v, vec.m_v, sizeof(m_v));
#endif
            }

            vec2::vec2(const vec2& origin, const vec2& destination) {
                m_v[0] = destination.m_v[0] - origin.m_v[0];
                m_v[1] = destination.m_v[1] - origin.m_v[1];
            }

            vec2& vec2::Normalize() {
                float t = (float)sqrtf(float(m_v[0] * m_v[0] + m_v[1] * m_v[1]));
                m_v[0] /= t;
                m_v[1] /= t;
                return *this;
            }

            const vec2 vec2::Normalized() const
            {
                vec2 res = *this;
                return res.Normalize();
            }

            float vec2::Length() const {
                return sqrtf(float(m_v[0] * m_v[0] + m_v[1] * m_v[1]));
            }

            float vec2::SqrLength() const {
                return m_v[0] * m_v[0] + m_v[1] * m_v[1];
            }

            vec2& vec2::Negate() {
                m_v[0] = -m_v[0];
                m_v[1] = -m_v[1];
                return *this;
            }

            const vec2 vec2::Negated() const {
                vec2 v = *this;
                return v.Negate();
            }

            vec2& vec2::Set(float x, float y) {
                m_v[0] = x;
                m_v[1] = y;
                return *this;
            }

            vec2 vec2::ComponentMult(const vec2& v) {
                return vec2(m_v[0]*v[0], m_v[1]*v[1]);
            }

            float vec2::Dot(const vec2& vec) {
                return m_v[0]*vec.m_v[0] + m_v[1]*vec.m_v[1];
            }

            const Core::String vec2::ToString() const {
                return Core::String(L"({0}; {1})").arg(m_v[0]).arg(m_v[1]);
            }

            const vec2 operator + (const vec2& v1, const vec2& v2) {
                return vec2(v1[0] + v2[0], v1[1] + v2[1]);
            }

            const vec2 operator - (const vec2& v1, const vec2& v2) {
                return vec2(v1[0] - v2[0], v1[1] - v2[1]);
            }

            const vec2 operator *(const vec2& v, float d) {
                return vec2(v[0] * d, v[1] * d);
            }

            const vec2 operator *(float d, const vec2 &v) {
                return vec2(v[0] * d, v[1] * d);
            }

            const vec2 operator / (const vec2& v, float d) {
                return vec2(v[0] / d, v[1] / d);
            }

            bool operator == (const vec2& a, const vec2& b) {
                return a[0] == b[0] && a[1] == b[1];
            }

            bool operator != (const vec2& a, const vec2& b) {
                return !(a == b);
            }

            //////////////////////////////////


            const int& ivec2::X() const {
                return m_v[0];
            }

            int& ivec2::X() {
                return m_v[0];
            }

            int& ivec2::Y() {
                return m_v[1];
            }

            const int& ivec2::Y() const {
                return m_v[1];
            }

            int& ivec2::R() {
                return m_v[0];
            }

            const int& ivec2::R() const {
                return m_v[0];
            }

            const int& ivec2::G() const {
                return m_v[1];
            }

            int& ivec2::G() {
                return m_v[1];
            }

            ivec2 ivec2::XY() const {
                return ivec2(m_v[0], m_v[1]);
            }

            ivec2::operator int* () {
                return &m_v[0];
            }

            int& ivec2::operator [] (int i) {
                return m_v[i];
            }

            const int& ivec2::operator [] (int i) const {
                return m_v[i];
            }

            ivec2& ivec2::operator = (const ivec2& vec) {
#ifdef _WIN32
                memcpy_s(m_v, sizeof(m_v), vec.m_v, sizeof(m_v));
#elif defined __gnu_linux__
                memcpy(m_v, vec.m_v, sizeof(m_v));
#endif
                return *this;
            }

            ivec2::ivec2() {
                memset(m_v, 0, sizeof(m_v));
            }

            ivec2::ivec2(int x, int y) {
                m_v[0] = x; m_v[1] = y;
            }

            ivec2::ivec2(const ivec2& vec) {
#ifdef _WIN32
                memcpy_s(m_v, sizeof(m_v), vec.m_v, sizeof(m_v));
#elif defined __gnu_linux__
                memcpy(m_v, vec.m_v, sizeof(m_v));
#endif
            }

            ivec2::ivec2(const ivec2& origin, const ivec2& destination) {
                m_v[0] = destination.m_v[0] - origin.m_v[0];
                m_v[1] = destination.m_v[1] - origin.m_v[1];
            }

            int ivec2::SqrLength() {
                return m_v[0] * m_v[0] + m_v[1] * m_v[1];
            }

            ivec2& ivec2::Negate() {
                m_v[0] = -m_v[0];
                m_v[1] = -m_v[1];
                return *this;
            }

            ivec2& ivec2::Set(int x, int y) {
                m_v[0] = x;
                m_v[1] = y;
                return *this;
            }

            ivec2 ivec2::ComponentMult(const ivec2& v) {
                return ivec2(m_v[0]*v[0], m_v[1]*v[1]);
            }

            int ivec2::Dot(const ivec2& vec) {
                return m_v[0]*vec[0] + m_v[1]*vec[1];
            }

            const Core::String ivec2::ToString() const {
                return Core::String(L"{0}; {1}").arg(m_v[0]).arg(m_v[1]);
            }

            const ivec2 operator + (const ivec2& v1, const ivec2& v2) {
                return ivec2(v1[0] + v2[0], v1[1] + v2[1]);
            }

            const ivec2 operator - (const ivec2& v1, const ivec2& v2) {
                return ivec2(v1[0] - v2[0], v1[1] - v2[1]);
            }

            const ivec2 operator *(const ivec2& v, int d) {
                return ivec2(v[0] * d, v[1] * d);
            }

            const ivec2 operator *(int d, const ivec2 &v) {
                return ivec2(v[0] * d, v[1] * d);
            }

            const ivec2 operator / (const ivec2& v, int d) {
                return ivec2(v[0] / d, v[1] / d);
            }

            bool operator == (const ivec2& a, const ivec2& b) {
                return a[0] == b[0] && a[1] == b[1];
            }

            bool operator != (const ivec2& a, const ivec2& b) {
                return !(a == b);
            }
        }
    }
}

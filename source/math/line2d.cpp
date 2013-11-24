#include "relations.h"
#include "line2d.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            Line2D::Line2D()
                : m_origin()
                , m_destination() {}

            Line2D::Line2D(const vec2& org, const vec2& dest)
                : m_origin(org)
                , m_destination(dest) {}

            Line2D::Line2D(const Line2D& line)
                : m_origin(line.m_origin)
                , m_destination(line.m_destination) {}

            Line2D& Line2D::Rotate() {
                vec2 m = 0.5f * (m_origin + m_destination);
                vec2 v = m_destination - m_origin;
                vec2 n = vec2(v.Y(), -v.X());
                m_origin = m - 0.5f * n;
                m_destination = m + 0.5f * n;
                return *this;
            }

            Line2D& Line2D::Flip() {
                return Rotate().Rotate();
            }

            const vec2 Line2D::Direction() const {
                return (m_destination - m_origin).Normalized();
            }

            float Line2D::SegmentLength() const {
                return (m_destination - m_origin).Length();
            }

            const vec2& Line2D::Origin() const {
                return m_origin;
            }

            vec2& Line2D::Origin() {
                return m_origin;
            }

            const vec2& Line2D::Destination() const {
                return m_destination;
            }

            vec2& Line2D::Destination() {
                return m_destination;
            }

            Relation CrossLine(const Line2D &l, const Line2D &r, float &t) {
                vec2 a = l.Origin();
                vec2 b = l.Destination();
                vec2 c = r.Origin();
                vec2 d = r.Destination();
                vec2 n = vec2((d - c).Y(), (c - d).X());
                float denom = n.Dot(b - a);
                if (denom == 0.0)
                {
                    Relation aclass = ClassifyPoint(l.Origin(), r);
                    if ((aclass == Relation::LEFT) || (aclass == Relation::RIGHT))
                        return Relation::PARALLEL;
                    else
                        return Relation::ON;
                }

                float num = n.Dot(a - c);
                t = -num / denom;

                return Relation::INTERSECT;
            }

            const vec2 Line2D::Point(float t) {
                return m_origin + t * (m_destination - m_origin);
            }

            float Distance(const vec2& p, const Line2D& line) {
                Line2D ab = Line2D(line);
                ab.Flip().Rotate();

                vec2 n = ab.Destination() - ab.Origin();

                n.Normalize();

                Line2D f = Line2D(p, p + n);
                float t = 0;
                CrossLine(f, line, t);
                return t;
            }
        }
    }
}

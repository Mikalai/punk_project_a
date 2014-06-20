#include "mat4.h"
#include "sphere.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            const Sphere operator * (const mat4& m, const Sphere& s)
            {
                Sphere res;
                res.m_center = m * s.GetCenter();
                //	consider that transform do not effect the radius
                res.m_radius = s.GetRadius();
                return res;
            }

            const Sphere operator + (const Sphere& a, const Sphere& b)
            {
                float d = (a.GetCenter() - b.GetCenter()).Length();
                if (d + a.GetRadius() <= b.GetRadius())
                    return b;
                if (d + b.GetRadius() <= a.GetRadius())
                    return a;

                Sphere res;
                float r = 0.5f * (d + a.GetRadius() + b.GetRadius());
                res.SetRadius(r);
                res.SetCenter(a.GetCenter() + (r - a.GetRadius()) / d * (b.GetCenter() - a.GetCenter()));
                return res;
            }
        }
    }
}

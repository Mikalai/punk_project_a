//#include "triangle2d.h"
//#include "absolute_value.h"
//#include <limits>

//namespace Punk {
//    namespace Engine {
//        namespace Math {

//            Triangle2D::Triangle2D()
//                : a()
//                , b()
//                , c() {}

//            Triangle2D::Triangle2D(const vec2& v0, const vec2& v1, const vec2& v2) {
//                //
//                //  c.X() must be between a and b
//                //
//                a = v0.X() < v1.X() ? (v0.X() < v2.X() ? v0 : v2) : (v1.X() < v2.X() ? v1 : v2);
//                b = v0.X() > v1.X() ? (v0.X() > v2.X() ? v0 : v2) : (v1.X() > v2.X() ? v1 : v2);
//                if ((v0 == a && v1 == b) || (v0 == b && v1 == a))
//                    c = v2;
//                else if ((v0 == a && v2 == b) || (v0 == b && v2 == a))
//                    c = v1;
//                else if ((v1 == a && v2 == b) || (v1 == b && v2 == a))
//                    c = v0;
//                else {
//                    a = b = c = (v0 + v1 + v2) / 3.0f;
//                    //   throw new EX()ception("Fuck!!! I made a stupid mistake in Triangle2D");
//                }
//            }


//        }
//    }
//}

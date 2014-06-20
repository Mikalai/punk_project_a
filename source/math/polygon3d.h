#ifndef _H_PUNK_MATH_POLYGON_3D
#define _H_PUNK_MATH_POLYGON_3D

#include <vector>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Math {

            namespace __private {
                struct Polygon3DImpl;
            }

            class vec3;

            class PUNK_ENGINE_API Polygon3D
            {
            public:
                Polygon3D();
                Polygon3D(const Polygon3D& value);
                Polygon3D& operator = (const Polygon3D& value);
                ~Polygon3D();

                void Append(const vec3& p);
                const vec3* GetPoints() const;
                std::size_t GetCount() const;

                bool IsPlanar();
                bool IsTriangle();

                //	modifies current polygon
                Polygon3D& MakePlanar();

                __private::Polygon3DImpl* impl;
            };
        }
    }
}

#endif

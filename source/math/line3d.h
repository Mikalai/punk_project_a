#ifndef LINE_H
#define LINE_H

#include "config.h"
#include "vec3.h"

namespace Punk {
    namespace Engine {
        namespace Core {
            class String;
        }

        namespace Math {
            class mat4;

            class PUNK_ENGINE_API Line3D {
            public:

                Line3D();
                Line3D(const vec3& org, const vec3& dir);
                const vec3 PointAt(float t) const;

                const vec3& GetDirection() const { return m_direction; }
                const vec3& GetOrigin() const { return m_origin; }
                const vec3& GetDestination() const { return m_destination; }

                void SetOrigin(const vec3& origin);
                void SetDestination(const vec3& destination);
                float SegmentLength() const;

                Line3D& SetOriginDirection(const vec3& org, const vec3& dir);
                Line3D& SetOriginDestination(const vec3& org, const vec3& dst);

                const Core::String ToString() const;
            private:
                vec3 m_origin;
                vec3 m_destination;
                vec3 m_direction;
            };

            const Line3D operator * (const mat4& l, const Line3D& r);
        }
    }
}

#endif // LINE_H

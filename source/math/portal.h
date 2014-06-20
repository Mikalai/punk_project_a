#ifndef _H_PUNK_MATH_PORTAL
#define _H_PUNK_MATH_PORTAL

#include <cstdint>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            namespace __private {
                struct PortalImpl;
            }

            class vec3;
            class mat4;

            class PUNK_ENGINE_API Portal
            {
            public:
                Portal();
                Portal(const Portal& value);
                Portal& operator = (const Portal& value);
                ~Portal();

                bool SetPoints(const vec3* points, std::uint32_t count);
                std::uint32_t GetSize() const;
                void SetSize(std::uint32_t value);
                const vec3& operator [] (std::uint32_t index) const;
                vec3& operator [] (std::uint32_t index);

                const vec3 GetNormal() const;
                float GetDistance() const;

                __private::PortalImpl* impl {nullptr};

                friend PUNK_ENGINE_API const Portal operator * (const mat4& m, const Portal& p);
            };

            //	transforms portal to other space
            PUNK_ENGINE_API const Portal operator * (const mat4& m, const Portal& p);
        }
    }
}

#endif	//	_H_PUNK_MATH_PORTAL

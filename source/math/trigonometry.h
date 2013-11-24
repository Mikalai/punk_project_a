#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H

#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            PUNK_ENGINE_API float Sin(float value);
            PUNK_ENGINE_API float Cos(float value);
            PUNK_ENGINE_API float ArcSin(float value);
            PUNK_ENGINE_API float ArcCos(float value);
            PUNK_ENGINE_API float Tan(float value);
            PUNK_ENGINE_API float ArcTan(float value);
            PUNK_ENGINE_API double Sin(double value);
            PUNK_ENGINE_API double Cos(double value);
            PUNK_ENGINE_API double ArcSin(double value);
            PUNK_ENGINE_API double ArcCos(double value);
            PUNK_ENGINE_API double Tan(double value);
            PUNK_ENGINE_API double ArcTan(double value);
        }
    }
}

#endif // TRIGONOMETRY_H

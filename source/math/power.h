#ifndef POWER_H
#define POWER_H

#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            PUNK_ENGINE_API float Pow(float value, float power);
            PUNK_ENGINE_API double Pow(double value, double power);
        }
    }
}

#endif // POWER_H

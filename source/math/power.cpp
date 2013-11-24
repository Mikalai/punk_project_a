#include <math.h>
#include "power.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            float Pow(float value, float power) {
                return (float)pow(value, power);
            }

            double Pow(double value, double power) {
                return pow(value, power);
            }
        }
    }
}

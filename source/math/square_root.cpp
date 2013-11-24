#include <math.h>
#include "square_root.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            float Sqrt(float value) {
                return (float)sqrt(value);
            }

            double Sqrt(double value) {
                return sqrt(value);
            }
        }
    }
}

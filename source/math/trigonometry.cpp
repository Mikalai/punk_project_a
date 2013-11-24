#include <math.h>
#include "trigonometry.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            float Sin(float value) {
                return (float)sin(value);
            }

            float Cos(float value) {
                return (float)cos(value);
            }

            float ArcSin(float value) {
                return (float)asin(value);
            }

            float ArcCos(float value) {
                return (float)acos(value);
            }

            float Tan(float value) {
                return (float)tan(value);
            }

            float ArcTan(float value) {
                return (float)atan(value);
            }

            double Sin(double value) {
                return sin(value);
            }

            double Cos(double value) {
                return cos(value);
            }

            double ArcSin(double value) {
                return asin(value);
            }

            double ArcCos(double value) {
                return acos(value);
            }

            double Tan(double value) {
                return tan(value);
            }

            double ArcTan(double value) {
                return atan(value);
            }
        }
    }
}

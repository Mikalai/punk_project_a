#ifndef ARRAY_H
#define ARRAY_H

#include <cstdint>
#include "config.h"

namespace Punk {
    namespace Engine {
        namespace Math {
            namespace __private {
                struct ArrayImpl;
            }

            class PUNK_ENGINE_API Array {
            public:
                Array();
                Array(const Array& value);
                Array& operator = (const Array& value);

                float& operator [] (std::size_t index);
                const float& operator [] (std::size_t index) const;
                std::size_t size() const;
                bool empty() const;
                void push_back(float value);
                void pop_back();
                float back();

                __private::ArrayImpl* impl;
            };
        }
    }
}

#endif // ARRAY_H

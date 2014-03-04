#ifndef VALUE_H
#define VALUE_H

#include <config.h>

PUNK_ENGINE_BEGIN
namespace Math{

    template<class T>
    class Value {
    public:
        operator T () {
            return m_cur;
        }

        void SetMin(const T& value) P
                m_min = value;
    }



    private:
    T m_min;
    T m_max;
    T m_cur;
};
}
PUNK_ENGINE_END

#endif // VALUE_H

#ifndef TIME_DEPENDENT_H
#define TIME_DEPENDENT_H

#include <config.h>
#include <core/iobject.h>
#include <chrono>

PUNK_ENGINE_BEGIN
DECLARE_PUNK_GUID(IID_ITimeDependent, "8CD2F9F1-FA3C-419D-8FE9-2E0031099993");

class ITimeDependent : public Core::IObject {
public:
    virtual void Update(const std::chrono::system_clock::time_point& current_time, std::chrono::system_clock::duration& delta) = 0;
};

PUNK_ENGINE_END


#endif // TIME_DEPENDENT_H

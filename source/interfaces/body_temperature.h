#ifndef BODY_TEMPERATURE_H
#define BODY_TEMPERATURE_H

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN


DECLARE_PUNK_GUID(IID_IBodyTemperature, "9F2DE9BE-D88E-456F-B983-CC2DFFAB0E2D");

class IBodyTemperature : public Core::IObject {
public:
    virtual std::double_t GetCurrentTemperature() const = 0;
    virtual void SetCurrentTemperature(std::double_t value) = 0;
    virtual std::double_t GetNormalTemperature() const = 0;
    virtual void SetNormalTemeperature(std::double_t value) = 0;
    virtual std::double_t GetMinimalTemperature() const = 0;
    virtual void SetMinimalTemperature(std::double_t value) = 0;
    virtual std::double_t GetMaximalTemperature() const = 0;
    virtual void SetMaximalTemperature(std::double_t value) = 0;
};

PUNK_ENGINE_END


#endif // BODY_TEMPERATURE_H

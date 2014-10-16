#ifndef BODY_POWER_H
#define BODY_POWER_H

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
class IBody;
class IHeatSources;

DECLARE_PUNK_GUID(IID_IObjectPower, "01CA6AEA-7DE5-42DA-9463-EAEFD62E2AEA");

class IBodyPower : public Core::IObject {
public:
    virtual std::double_t GetTotalConsumption() const = 0;
    virtual std::double_t GetMetabolismConstant() const = 0;
    virtual std::double_t GetMetabolism() const = 0;
    virtual std::double_t GetActivity() const = 0;
    virtual std::double_t GetExaporative() const = 0;
    virtual std::double_t GetHeatConvection() const = 0;
    virtual std::double_t GetEvaporation() const = 0;
    virtual std::double_t GetMaximalEvaporation() const = 0;
    virtual std::double_t GetSurplus() const = 0;
    virtual std::double_t GetLongWaveRadiation() const = 0;
    virtual std::double_t GetShortWaveRadiation(IHeatSources* heat_sources) const = 0;
    virtual std::double_t GetRadiation(IHeatSources* heat_sources) const = 0;
};

void UpdateHeatBalance(IBody* body, IBodyPower* power);

PUNK_ENGINE_END

#endif // BODY_POWER_H

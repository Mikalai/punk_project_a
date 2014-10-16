#ifndef BODY_PART_H
#define BODY_PART_H

#include <config.h>
#include <core/iobject.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN
DECLARE_PUNK_GUID(IID_IBodyPart, "DF7AA813-2F36-4063-A195-E0D5F44F2CAD");

class IBodyPart : public Core::IObject {
public:
    virtual std::double_t GetHeatRadiationAbsorbingFactor() const = 0;
    virtual void SetHeatRadiationAbsorbingFactor(std::double_t value) = 0;
    virtual std::double_t GetWindProtectionFactor() const = 0;
    virtual void SetWindoProtectionFactor(std::double_t value) = 0;
    virtual std::double_t GetWeightFactor() const = 0;
    virtual void SetWeightFactor(std::double_t value) = 0;
    virtual Core::String GetName() const = 0;
    virtual void SetName(const Core::String& value) = 0;
};

PUNK_ENGINE_END

#endif // BODY_PART_H

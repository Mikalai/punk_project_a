#ifndef LOCATION_H
#define LOCATION_H

#include <config.h>
#include <core/iobject.h>
#include <math/forward.h>
PUNK_ENGINE_BEGIN

DECLARE_PUNK_GUID(IID_ILocation, "9714b965-cce1-4182-8879-5dd09380ba39");

class ILocation : public Core::IObject {
public:
    virtual ILocation* GetParentLocation() = 0;
    virtual const ILocation* GetParentLocation() const = 0;
    virtual void SetParentLocation(ILocation* value) = 0;
    virtual std::uint32_t GetChildLocationsCount() const = 0;
    virtual ILocation* GetChildLocation(std::uint32_t index) = 0;
    virtual const ILocation* GetChildLocation(std::uint32_t index) const = 0;
    virtual Math::vec2 GetGlobalPosition() const = 0;
    virtual Math::vec2 GetLocalPosition() const = 0;
    virtual std::double_t GetDistance(const ILocation* location) const = 0;
    virtual void Move(const Math::vec2& delta) = 0;
    virtual void Rotate(float delta) = 0;
};

PUNK_ENGINE_END

#endif // LOCATION_H

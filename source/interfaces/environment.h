#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN

class IHeatSource : public Core::IObject {
public:
    virtual std::double_t GetSurfacePower(std::double_t distance_to_source) const = 0;
    virtual std::double_t GetSurfacePower() const = 0;
    virtual void SetPower(std::double_t value) const = 0;
};

class IHeatSources : public Core::IObject {
public:
    virtual std::list<IHeatSource*>* GetHeatSources() = 0;
    virtual const std::list<IHeatSource*>* GetHeatSources() const = 0;
};

PUNK_ENGINE_END

#endif // ENVIRONMENT_H

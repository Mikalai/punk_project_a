#ifndef BODY_H
#define BODY_H

#include <list>
#include <config.h>
#include <core/iobject.h>
#include <core/action.h>
#include "body_action.h"

PUNK_ENGINE_BEGIN

DECLARE_PUNK_GUID(IID_IBody, "E6768CF9-DF23-48B5-88A6-003D35D10182");

enum class BodyGender {
    Male,
    Female,
    Trans
};

class IBodyAction;
class IBodyPart;

using MassChangedDelegate = Core::ActionBase<std::double_t, std::double_t>*;

class IBody : public Core::IObject {
public:
    virtual std::double_t GetMass() const = 0;
    virtual void SetMass(std::double_t value) = 0;
    virtual std::double_t GetStrength() const = 0;
    virtual std::double_t GetRelativeStrength() const = 0;
    virtual std::double_t GetMuscle() const = 0;
    virtual void SetMuscle(std::double_t value) = 0;
    virtual std::double_t GetFat() const = 0;
    virtual void SetFat(std::double_t value) = 0;
    virtual BodyGender GetGender() const = 0;
    virtual void SetGender(BodyGender value) = 0;
    virtual std::double_t GetHeatRadiationAbsorbingFactor() const = 0;
    virtual std::double_t GetWindProtectionFactor() const = 0;
    virtual std::double_t GetBodySurface() const = 0;
    virtual std::double_t GetSpecificHeat() const = 0;


    //    virtual std::list<IBodyAction*>* GetCurrentActions() = 0;
    //    virtual const std::list<IBodyAction*>* GetCurrentActions() const = 0;
    //    virtual std::list<IBodyPart*>* GetBodyParts() = 0;
    //    virtual const std::list<IBodyPart*>* GetBodyParts() const = 0;

};

PUNK_ENGINE_END

#endif // BODY_H

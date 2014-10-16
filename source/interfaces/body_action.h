#ifndef BODY_ACTION_H
#define BODY_ACTION_H

#include <config.h>
#include <core/iobject.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN

enum class BodyActivityLevel {
    Minimal,
    Low,
    Average,
    High,
    VeryHigh
};

DECLARE_PUNK_GUID(IID_IBodyAction, "05469F3B-62ED-4756-ADC0-206E04F9EDAA");
class IBodyAction : public Core::IObject {
public:
    virtual BodyActivityLevel GetActivityLevel() const = 0;
    virtual void SetActivityLevel(BodyActivityLevel value) = 0;
    virtual const Core::String GetActivityName() const = 0;
    virtual void SetActivityName(const Core::String& value) = 0;
    virtual std::double_t GetActivityPowerConsumption() const = 0;
    virtual void SetActivityPowerConsumption(std::double_t value) = 0;
};

DECLARE_PUNK_GUID(IID_IBodyActions, "3fd2fbde-a401-4a89-ab24-3bae0e82c72f");
class IBodyActions : public Core::IObject {
public:
    virtual std::list<IBodyAction*>* GetBodyActions() = 0;
    virtual std::list<IBodyAction*>* GetBodyActions() const = 0;
    virtual bool IsDoing(const Core::String& name) const = 0;
    virtual const IBodyAction* FindBodyAction(const Core::String& name) const = 0;
    virtual std::double_t GetActivityTotalPowerConsumption() const = 0;
};

PUNK_ENGINE_END

#endif // BODY_ACTION_H

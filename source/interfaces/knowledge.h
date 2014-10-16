#ifndef KNOWLEDGE_H
#define KNOWLEDGE_H

#include <list>
#include <config.h>
#include <core/iobject.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN

DECLARE_PUNK_GUID(IID_IKnowledge, "F1BBA044-591C-4537-A46D-FCE6355249FE");

class IKnowledge : public Core::IObject {
public:
    virtual std::list<IKnowledge*>* GetDependencyList() = 0;
    virtual const Core::String GetName() = 0;
    virtual void SetName(const Core::String& value) = 0;
    virtual const Core::String GetDescription() = 0;
    virtual void SetDescription(const Core::String& value) = 0;
    virtual std::uint32_t GetId() const = 0;
    virtual void SetId(std::uint32_t value) = 0;
};

PUNK_ENGINE_END

#endif // KNOWLEDGE_H

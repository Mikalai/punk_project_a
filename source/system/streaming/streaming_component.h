#ifndef STREAMING_COMPONENT_H
#define STREAMING_COMPONENT_H

#include "system/component/module.h"
#include "async_loader.h"

namespace System
{    
    class PUNK_ENGINE_LOCAL StreamingComponent : public Component
    {
    public:
        virtual ~StreamingComponent();        
        const string GetName() const override;
        const StringList GetServicesList() const override;
    protected:
        void OnInitialize() override;
        Object* OnGetService(const string& name) override;
    private:        
        void Clear();
        void Create();
        AsyncLoader* m_loader {nullptr};
    };
}

#endif // STREAMING_COMPONENT_H

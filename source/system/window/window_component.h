#ifndef WINDOW_COMPONENT_H
#define WINDOW_COMPONENT_H

#include "system/component/module.h"
#include "system/window/window_description.h"

namespace System
{
    class Window;
    class PUNK_ENGINE_LOCAL WindowComponent : public Component
    {
    public:
        WindowComponent();
        virtual ~WindowComponent() override;        
        const string GetName() const override;
        const StringList GetServicesList() const override;

    protected:
        void OnInitialize() override;
        void OnDetach() override;
        Object* OnGetService(const string& name) override;

    private:
        void Create();
        void Clear();

        WindowDesc m_desc;  // TODO: Should be loaded from file at start up
        Window* m_window;
    };
}

#endif // WINDOW_COMPONENT_H

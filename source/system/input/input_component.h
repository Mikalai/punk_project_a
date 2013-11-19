#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "system/component/module.h"

namespace System
{
    class Mouse;
    class Keyboard;
    class KeyMap;

    class PUNK_ENGINE_LOCAL InputComponent : public Component
    {
    public:
        InputComponent();
        virtual ~InputComponent();

    protected:
        virtual void OnDetach();
        virtual void OnInitialize();
        Object* OnGetService(const string& name) override;

    private:
        void Create();
        void Clear();
        Mouse* m_mouse {nullptr};
        Keyboard* m_keyboard {nullptr};
        KeyMap* m_key_map {nullptr};
    };
}

#endif // INPUT_COMPONENT_H

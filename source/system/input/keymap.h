#ifndef KEYMAP_H
#define KEYMAP_H

#include <set>
#include <map>
#include <array>
#include "core/action.h"
#include "core/object.h"
#include "keymap_interface.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class KeyEvent;

    struct KeyMapImpl;

    class KeyMap final : public IKeyMap, public Core::Object
    {
    public:
        KeyMap();
        virtual ~KeyMap();

        void OnKeyEvent(const KeyEvent& event) override;
        void Add(Key key, KeyboardAction action) override;
        void Remove(Key key, KeyboardAction action) override;
        std::set<KeyboardAction>& GetActions(Key key) override;
        const std::set<KeyboardAction>& GetActions(Key key) const override;

        PUNK_OBJECT(KeyMap) //  TODO: Keymap can be saved

        KeyMapImpl* impl;
    };
}
PUNK_ENGINE_END

#endif // KEYMAP_H

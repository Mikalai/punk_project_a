#ifndef KEYMAP_H
#define KEYMAP_H

#include <set>
#include <map>
#include <array>
#include "core/action.h"
#include "ikeymap.h"

PUNK_ENGINE_BEGIN
namespace System
{
    class KeyEvent;

    struct KeyMapImpl;

    class PUNK_ENGINE_LOCAL KeyMap final : public IKeyMap
    {
    public:
        KeyMap();
        virtual ~KeyMap();

		void QueryInterface(const Core::Guid& type, void** object) override;
        void OnKeyEvent(const KeyEvent& event) override;
        void Add(Key key, KeyboardAction action) override;
        void Remove(Key key, KeyboardAction action) override;
        std::set<KeyboardAction>& GetActions(Key key) override;
        const std::set<KeyboardAction>& GetActions(Key key) const override;
        
        KeyMapImpl* impl;

		PUNK_OBJECT_DEFAULT_IMPL(KeyMap) //  TODO: Keymap can be saved
    };
}
PUNK_ENGINE_END

#endif // KEYMAP_H

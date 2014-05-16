#ifndef KEYMAP_INTERFACE_H
#define KEYMAP_INTERFACE_H

#include <map>
#include <set>
#include <config.h>
#include <core/iobject.h>
#include <core/action.h>

PUNK_ENGINE_BEGIN
namespace System {
    class KeyEvent;

    using Key = int;
    using KeyboardAction = Core::ActionBasePtr<const KeyEvent&>;
    using KeyboardActionsCollection = std::map<Key, std::set<KeyboardAction>>;

	static const Core::Guid IID_IKeyMap{ "2F416318-72A8-449B-9216-3E25352B8B09" };

	class PUNK_ENGINE_API IKeyMap : public Core::IObject
    {
    public:
        virtual void OnKeyEvent(const KeyEvent& event) = 0;
        virtual void Add(Key key, KeyboardAction action) = 0;
        virtual void Remove(Key key, KeyboardAction action) = 0;
        virtual std::set<KeyboardAction>& GetActions(Key key) = 0;
        virtual const std::set<KeyboardAction>& GetActions(Key key) const = 0;
    };
}
PUNK_ENGINE_END

#endif // KEYMAP_INTERFACE_H

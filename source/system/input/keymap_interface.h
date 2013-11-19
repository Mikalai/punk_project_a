#ifndef KEYMAP_INTERFACE_H
#define KEYMAP_INTERFACE_H

#include <set>

namespace System
{
    class KeyEvent;

    using Key = int;
    using KeyboardAction = ActionBasePtr<const KeyEvent&>;
    using KeyboardActionsCollection = std::map<Key, std::set<KeyboardAction>>;

    class IKeyMap
    {
    public:
        virtual void OnKeyEvent(const KeyEvent& event) = 0;
        virtual void Add(Key key, KeyboardAction action) = 0;
        virtual void Remove(Key key, KeyboardAction action) = 0;
        virtual std::set<KeyboardAction>& GetActions(Key key) = 0;
        virtual const std::set<KeyboardAction>& GetActions(Key key) const = 0;
    };
}

#endif // KEYMAP_INTERFACE_H

#include "errors/module.h"
#include "keymap.h"

namespace System
{
    PUNK_OBJECT_REG(KeyMap, "System.KeyMap", typeid(KeyMap).hash_code(), nullptr, nullptr, &Object::Info.Type);

    struct KeyMapImpl
    {
        ~KeyMapImpl()
        {
            for (auto key : m_actions)
            {
                for (auto action : key.second)
                {
                    action->Release();
                }
            }
        }

        KeyboardActionsCollection m_actions;
    };

    void KeyMap::Add(Key key, KeyboardAction action)
    {
        impl->m_actions[key].insert(action);
        action->AddRef();
    }

    void KeyMap::Remove(Key key, KeyboardAction action)
    {
        auto key_it = impl->m_actions.find(key);
        if (key_it == impl->m_actions.end())
            return;
        auto action_it = key_it->second.find(action);
        if (key_it->second.end() == action_it)
            return;
        key_it->second.erase(action_it);
        action->Release();
    }

    std::set<KeyboardAction>& KeyMap::GetActions(Key key)
    {
        return impl->m_actions[key];
    }

    const std::set<KeyboardAction>& KeyMap::GetActions(Key key) const
    {
        auto it = impl->m_actions.find(key);
        if (it == impl->m_actions.end())
            throw PunkException("Key was not found");
        return it->second;
    }

    KeyMap::KeyMap()
        : impl(new KeyMapImpl)
    {
        Info.Add(this);
    }

    KeyMap::~KeyMap()
    {        
        delete impl;
        impl = nullptr;
        Info.Remove(this);
    }
}

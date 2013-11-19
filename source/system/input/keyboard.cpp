#include "keyboard.h"
#include <memory.h>

namespace System
{
    PUNK_OBJECT_REG(Keyboard, "System.Keyboard", typeid(Keyboard).hash_code(), nullptr, nullptr, &Object::Info.Type);

    struct KeyboardImpl
    {
        KeyboardImpl()
        {
            memset(m_keys, 0, sizeof(m_keys));
        }

        bool m_keys[256];
    };

	Keyboard::Keyboard() 
        : impl(new KeyboardImpl)
    {
        Info.Add(this);
    }

    Keyboard::~Keyboard()
    {
        Info.Remove(this);
        delete impl;
        impl = nullptr;
    }

	bool& Keyboard::operator[] (int key)
	{
        return impl->m_keys[key];
	}

	const bool& Keyboard::operator[] (int key) const
	{
        return impl->m_keys[key];
	}

	void Keyboard::SetKeyState(int key, bool state)
	{
        impl->m_keys[key] = state;
	}

	bool Keyboard::GetKeyState(int key) const
	{		
        return impl->m_keys[key];
	}

    bool (*Keyboard::GetKeyStates())[256]
    {
        return &impl->m_keys;
    }
}

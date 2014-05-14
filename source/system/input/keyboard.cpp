#include "keyboard.h"
#include "system/logger/module.h"
#include <memory.h>

PUNK_ENGINE_BEGIN
namespace System {

    struct KeyboardImpl {
        KeyboardImpl() {
            memset(m_keys, 0, sizeof(m_keys));
        }
        bool m_keys[256];
    };

	Keyboard::Keyboard() 
        : impl(new KeyboardImpl)
		, m_container{ this, Core::GetRootObject() } {
        GetDefaultLogger()->Info("Keyboard created");
    }

    Keyboard::~Keyboard() {
        delete impl;
        impl = nullptr;
        GetDefaultLogger()->Info("Keyboard destroyed");
    }

    bool& Keyboard::operator[] (int key) {
        return impl->m_keys[key];
	}

    const bool& Keyboard::operator[] (int key) const {
        return impl->m_keys[key];
	}

	void Keyboard::SetKeyState(int key, bool state)	{
        impl->m_keys[key] = state;
	}

    bool Keyboard::GetKeyState(int key) const {
        return impl->m_keys[key];
	}

    IKeyBoard* GetKeyboard() {
        static Keyboard* keyboard = nullptr;
        if (!keyboard)
            keyboard = new Keyboard;
        return keyboard;
    }

    bool (*Keyboard::GetKeyStates())[256] {
        return &impl->m_keys;
    }
}
PUNK_ENGINE_END

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
		, m_ref_count{ 0 }
	{
        GetDefaultLogger()->Info("Keyboard created");
    }

    Keyboard::~Keyboard() {
        delete impl;
        impl = nullptr;
        GetDefaultLogger()->Info("Keyboard destroyed");
    }

	void Keyboard::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IKeyboard });
	}

	std::uint32_t Keyboard::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	std::uint32_t Keyboard::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
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

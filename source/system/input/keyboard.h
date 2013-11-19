#ifndef _H_PUNK_KEYBOARD_WIN32
#define _H_PUNK_KEYBOARD_WIN32

#include "system/core/object.h"
#include "keyboard_interface.h"

namespace System
{
    struct KeyboardImpl;

    class PUNK_ENGINE_API Keyboard final : public IKeyBoard, public Object
	{	
	public:
		Keyboard();
        virtual ~Keyboard();
        const bool& operator[] (int key) const override;
        bool& operator[] (int key) override;
        void SetKeyState(int key, bool state) override;
        bool GetKeyState(int key) const override;
        bool (*GetKeyStates() override)[256];
        KeyboardImpl* impl;

        PUNK_OBJECT(Keyboard)
	};
}

#endif

#ifndef _H_PUNK_KEYBOARD_WIN32
#define _H_PUNK_KEYBOARD_WIN32

#include "core/iobject.h"
#include "keyboard_interface.h"

PUNK_ENGINE_BEGIN
namespace System
{
    struct KeyboardImpl;

    class PUNK_ENGINE_LOCAL Keyboard final : public IKeyBoard
	{	
	public:
		Keyboard();
        virtual ~Keyboard();        
        const bool& operator[] (int key) const override;
        bool& operator[] (int key) override;
        void SetKeyState(int key, bool state) override;
        bool GetKeyState(int key) const override;
		void QueryInterface(std::uint64_t type, void** object) override;
        bool (*GetKeyStates() override)[256];
        KeyboardImpl* impl;        

		PUNK_OBJECT_DEFAULT_IMPL3(Keyboard)
	};    
}
PUNK_ENGINE_END

#endif

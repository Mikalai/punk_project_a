#ifndef _H_PUNK_KEYBOARD_WIN32
#define _H_PUNK_KEYBOARD_WIN32

#include "core/iobject.h"
#include "ikeyboard.h"

PUNK_ENGINE_BEGIN
namespace System
{
    struct KeyboardImpl;

    class PUNK_ENGINE_LOCAL Keyboard final : public IKeyBoard
	{	
	public:
		Keyboard();
        virtual ~Keyboard();        
		
		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IKeyboard
        const bool& operator[] (int key) const override;
        bool& operator[] (int key) override;
        void SetKeyState(int key, bool state) override;
        bool GetKeyState(int key) const override;
        bool (*GetKeyStates() override)[256];
        KeyboardImpl* impl;        
	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
	};    
}
PUNK_ENGINE_END

#endif

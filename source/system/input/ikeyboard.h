#ifndef KEYBOARD_INTERFACE_H
#define KEYBOARD_INTERFACE_H

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace System
{
	static const Core::Guid IID_IKeyboard{ "F9D3A077-12AF-4FB2-9FB0-17F0326E3A7D" };

	class IKeyBoard : public Core::IObject
    {
    public:
        virtual const bool& operator[] (int key) const = 0;
        virtual bool& operator[] (int key) = 0;
        virtual void SetKeyState(int key, bool state) = 0;
        virtual bool GetKeyState(int key) const = 0;
        virtual bool (*GetKeyStates())[256] = 0;
    };

    PUNK_ENGINE_API IKeyBoard* GetKeyboard();
}
PUNK_ENGINE_END

#endif // KEYBOARD_INTERFACE_H

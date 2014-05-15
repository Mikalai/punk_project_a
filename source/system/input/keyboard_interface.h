#ifndef KEYBOARD_INTERFACE_H
#define KEYBOARD_INTERFACE_H

#include <config.h>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace System
{
	class IKeyBoard : public virtual Core::IObject
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

#ifndef KEYBOARD_INTERFACE_H
#define KEYBOARD_INTERFACE_H

namespace System
{
    class IKeyBoard
    {
    public:
        virtual const bool& operator[] (int key) const = 0;
        virtual bool& operator[] (int key) = 0;
        virtual void SetKeyState(int key, bool state) = 0;
        virtual bool GetKeyState(int key) const = 0;
        virtual bool (*GetKeyStates())[256] = 0;
    };
}

#endif // KEYBOARD_INTERFACE_H

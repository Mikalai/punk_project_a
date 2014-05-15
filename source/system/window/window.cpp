#include "window.h"
#include "win32_window.h"
#include "x11_window.h"

PUNK_ENGINE_BEGIN
namespace System {

    Window::Window()
		: m_container{ this, Core::GetRootObject() }
    {
    }

    Window::~Window()
    {
    }
	
	void Window::QueryInterface(std::uint64_t type, void** object) {
		if (type == typeid(IWindow).hash_code() ||
			type == typeid(Core::IObject).hash_code()) {
			*object = (void*)this;
			AddRef();
		}
		else
			*object = nullptr;
	}

    void Window::SubscribeResizeEvent(ResizeEventDelegate delegate) {
        OnResizeEvent.Add(delegate);
    }

    void Window::UnsubscribeResizeEvent(ResizeEventDelegate delegate) {
        OnResizeEvent.Remove(delegate);
    }

    void Window::SubscribeKeyEvent(KeyEventDelegate delegate) {
        OnKeyEvent.Add(delegate);
    }

    void Window::UnsubscribeKeyEvent(KeyEventDelegate delegate) {
        OnKeyEvent.Remove(delegate);
    }

    void Window::SubscribeCharEvent(CharEventDelegate delegate) {
        OnCharEvent.Add(delegate);
    }

    void Window::UnsubscribeCharEvent(CharEventDelegate delegate){
        OnCharEvent.Remove(delegate);
    }

    void Window::SubscribeMouseEvent(MouseEventDelegate delegate){
        OnMouseEvent.Add(delegate);
    }

    void Window::UnsubscribeMouseEvent(MouseEventDelegate delegate){
        OnMouseEvent.Remove(delegate);
    }

    void Window::SubscribeMouseEvent(void (*Delegate)(const MouseEvent&)) {
        OnMouseEvent.Add(Delegate);
    }

    void Window::UnsubscribeMouseEvent(void (*Delegate)(const MouseEvent&)) {
        OnMouseEvent.Remove(Delegate);
    }

    void Window::SubscribeMouseMoveEvent(MouseMoveEventDelegate delegate){
        OnMouseMoveEvent.Add(delegate);
    }

    void Window::UnsubscribeMouseMoveEvent(MouseMoveEventDelegate delegate){
        OnMouseMoveEvent.Remove(delegate);
    }

    void Window::SubscribeMouseHooverEvent(MouseHooverEventDelegate delegate){
        OnMouseHooverEvent.Add(delegate);
    }

    void Window::UnsubscribeMouseHooverEvent(MouseHooverEventDelegate delegate){
        OnMouseHooverEvent.Remove(delegate);
    }

    void Window::SubscribeMouseWheelEvent(MouseWheelEventDelegate delegate){
        OnMouseWheelEvent.Add(delegate);
    }

    void Window::UnsubscribeMouseWheelEvent(MouseWheelEventDelegate delegate){
        OnMouseWheelEvent.Remove(delegate);
    }

    void Window::SubscribeWindowCreatedEvent(WindowCreatedDelegate delegate) {
        OnWindowCreated.Add(delegate);
    }

    void Window::UnsubscribeWindowCreatedEvent(WindowCreatedDelegate delegate) {
        OnWindowCreated.Remove(delegate);
    }

    void Window::SubscribeWindowDestroyEvent(WindowDestroyDelegate delegate) {
        OnWindowDestroy.Add(delegate);
    }

    void Window::SubscribeWindowDestroyEvent(void (*delegate)()) {
        OnWindowDestroy.Add(delegate);
    }

    void Window::UnsubscribeWindowDestroyEvent(WindowDestroyDelegate delegate) {
        OnWindowDestroy.Remove(delegate);
    }

    void Window::UnsubscribeWindowDestroyEvent(void (*delegate)()) {
        OnWindowDestroy.Remove(delegate);
    }

    void Window::SubscribeIdleEvent(IdleEventDelegate delegate) {
        OnIdleEvent.Add(delegate);
    }

    void Window::UnsubscribeIdleEvent(IdleEventDelegate delegate) {
        OnIdleEvent.Remove(delegate);
    }

    void Window::SubscribeIdleEvent(void (*Delegate)(const IdleEvent&)) {
        OnIdleEvent.Add(Delegate);
    }

    void Window::UnsubscribeIdleEvent(void (*Delegate)(const IdleEvent&)) {
        OnIdleEvent.Remove(Delegate);
    }

    void Window::Open() {
        if (!m_initialized) {
            InternalCreate();
            m_initialized = true;
        }
    }

    void Window::Close() {
        if (m_initialized) {
            InternalDestroy();
            m_initialized = false;
        }
    }
}
PUNK_ENGINE_END

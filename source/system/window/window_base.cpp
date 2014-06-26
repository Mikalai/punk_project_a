#include "window_base.h"

PUNK_ENGINE_BEGIN
namespace System {

    WindowBase::WindowBase()		
    {
    }

    WindowBase::~WindowBase()
    {
    }
	
    void WindowBase::SubscribeResizeEvent(ResizeEventDelegate delegate) {
        OnResizeEvent.Add(delegate);
    }

    void WindowBase::UnsubscribeResizeEvent(ResizeEventDelegate delegate) {
        OnResizeEvent.Remove(delegate);
    }

    void WindowBase::SubscribeKeyEvent(KeyEventDelegate delegate) {
        OnKeyEvent.Add(delegate);
    }

    void WindowBase::UnsubscribeKeyEvent(KeyEventDelegate delegate) {
        OnKeyEvent.Remove(delegate);
    }

    void WindowBase::SubscribeCharEvent(CharEventDelegate delegate) {
        OnCharEvent.Add(delegate);
    }

    void WindowBase::UnsubscribeCharEvent(CharEventDelegate delegate){
        OnCharEvent.Remove(delegate);
    }

    void WindowBase::SubscribeMouseEvent(MouseEventDelegate delegate){
        OnMouseEvent.Add(delegate);
    }

    void WindowBase::UnsubscribeMouseEvent(MouseEventDelegate delegate){
        OnMouseEvent.Remove(delegate);
    }

    void WindowBase::SubscribeMouseEvent(void (*Delegate)(const MouseEvent&)) {
        OnMouseEvent.Add(Delegate);
    }

    void WindowBase::UnsubscribeMouseEvent(void (*Delegate)(const MouseEvent&)) {
        OnMouseEvent.Remove(Delegate);
    }

    void WindowBase::SubscribeMouseMoveEvent(MouseMoveEventDelegate delegate){
        OnMouseMoveEvent.Add(delegate);
    }

    void WindowBase::UnsubscribeMouseMoveEvent(MouseMoveEventDelegate delegate){
        OnMouseMoveEvent.Remove(delegate);
    }

    void WindowBase::SubscribeMouseHooverEvent(MouseHooverEventDelegate delegate){
        OnMouseHooverEvent.Add(delegate);
    }

    void WindowBase::UnsubscribeMouseHooverEvent(MouseHooverEventDelegate delegate){
        OnMouseHooverEvent.Remove(delegate);
    }

    void WindowBase::SubscribeMouseWheelEvent(MouseWheelEventDelegate delegate){
        OnMouseWheelEvent.Add(delegate);
    }

    void WindowBase::UnsubscribeMouseWheelEvent(MouseWheelEventDelegate delegate){
        OnMouseWheelEvent.Remove(delegate);
    }

    void WindowBase::SubscribeWindowCreatedEvent(WindowCreatedDelegate delegate) {
        OnWindowCreated.Add(delegate);
    }

    void WindowBase::UnsubscribeWindowCreatedEvent(WindowCreatedDelegate delegate) {
        OnWindowCreated.Remove(delegate);
    }

    void WindowBase::SubscribeWindowDestroyEvent(WindowDestroyDelegate delegate) {
        OnWindowDestroy.Add(delegate);
    }

    void WindowBase::SubscribeWindowDestroyEvent(void (*delegate)()) {
        OnWindowDestroy.Add(delegate);
    }

    void WindowBase::UnsubscribeWindowDestroyEvent(WindowDestroyDelegate delegate) {
        OnWindowDestroy.Remove(delegate);
    }

    void WindowBase::UnsubscribeWindowDestroyEvent(void (*delegate)()) {
        OnWindowDestroy.Remove(delegate);
    }

    void WindowBase::SubscribeIdleEvent(IdleEventDelegate delegate) {
        OnIdleEvent.Add(delegate);
    }

    void WindowBase::UnsubscribeIdleEvent(IdleEventDelegate delegate) {
        OnIdleEvent.Remove(delegate);
    }

    void WindowBase::SubscribeIdleEvent(void (*Delegate)(const IdleEvent&)) {
        OnIdleEvent.Add(Delegate);
    }

    void WindowBase::UnsubscribeIdleEvent(void (*Delegate)(const IdleEvent&)) {
        OnIdleEvent.Remove(Delegate);
    }

    void WindowBase::Open() {
        if (!m_initialized) {
            InternalCreate();
            m_initialized = true;
        }
    }

    void WindowBase::Close() {
        if (m_initialized) {
            InternalDestroy();
            m_initialized = false;
        }
    }
}
PUNK_ENGINE_END

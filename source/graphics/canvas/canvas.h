#ifndef Graphics_COMMON_CONFIG_H
#define Graphics_COMMON_CONFIG_H

#ifdef _WIN32
#include <graphics/opengl/module.h>
#endif

#include <config.h>
#include <system/window/win32_window.h>
#include "canvas_desciption.h"
#include "icanvas.h"

PUNK_ENGINE_BEGIN
namespace System { class ILogger; }
namespace Graphics {

    class PUNK_ENGINE_LOCAL Canvas : public System::IWindow, public ICanvas {
    public:
        Canvas();
        ~Canvas();

		void Initialize(const CanvasDescription& desc = CanvasDescription()) override;

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;

		//	ICanvas
        void SetFullscreen(bool value) override;
        System::IWindow* GetWindow() override;
        const CanvasDescription& GetDescription() override;
        IVideoDriver* GetVideoDriver() override;
        void SwapBuffers() override;

		//	IWindow
		void Initialize(const System::WindowDescription& desc) override;
		int GetDesktopWidth() const override;
		int GetDesktopHeight() const override;
		int GetDesktopBitsPerPixel() const override;
		int GetDesktopRefreshRate() const override;
		int GetWidth() const override;
		int GetHeight() const override;
		int GetX() const override;
		int GetY() const override;
		void SetSize(int width, int height) override;
		void SetPosition(int x, int y) override;
		int Update(int dt) override;
		int Loop() override;
		void BreakMainLoop() override;
		void SetTitle(const Core::String& text) override;
		const Core::String GetTitle() const override;
		void Quite() override;
		void ShowCursor(bool value) override;
		void SubscribeResizeEvent(System::ResizeEventDelegate) override;
		void UnsubscribeResizeEvent(System::ResizeEventDelegate) override;
		void SubscribeKeyEvent(System::KeyEventDelegate) override;
		void UnsubscribeKeyEvent(System::KeyEventDelegate) override;
		void SubscribeCharEvent(System::CharEventDelegate) override;
		void UnsubscribeCharEvent(System::CharEventDelegate) override;
		void SubscribeMouseEvent(System::MouseEventDelegate) override;
		void UnsubscribeMouseEvent(System::MouseEventDelegate) override;
		void SubscribeMouseEvent(void(*Delegate)(const System::MouseEvent&)) override;
		void UnsubscribeMouseEvent(void(*Delegate)(const System::MouseEvent&)) override;
		void SubscribeMouseMoveEvent(System::MouseMoveEventDelegate) override;
		void UnsubscribeMouseMoveEvent(System::MouseMoveEventDelegate) override;
		void SubscribeMouseHooverEvent(System::MouseHooverEventDelegate) override;
		void UnsubscribeMouseHooverEvent(System::MouseHooverEventDelegate) override;
		void SubscribeMouseWheelEvent(System::MouseWheelEventDelegate) override;
		void UnsubscribeMouseWheelEvent(System::MouseWheelEventDelegate) override;
		void SubscribeWindowCreatedEvent(System::WindowCreatedDelegate) override;
		void UnsubscribeWindowCreatedEvent(System::WindowCreatedDelegate) override;
		void SubscribeWindowDestroyEvent(System::WindowDestroyDelegate) override;
		void SubscribeWindowDestroyEvent(void(*Delegate)()) override;
		void UnsubscribeWindowDestroyEvent(System::WindowDestroyDelegate) override;
		void UnsubscribeWindowDestroyEvent(void(*Delegate)()) override;
		void SubscribeIdleEvent(System::IdleEventDelegate) override;
		void UnsubscribeIdleEvent(System::IdleEventDelegate) override;
		void SubscribeIdleEvent(void(*Delegate)(const System::IdleEvent&)) override;
		void UnsubscribeIdleEvent(void(*Delegate)(const System::IdleEvent&)) override;
		void Open() override;
		void Close() override;
#ifdef _WIN32
		HWND GetNativeHandle() override;
#endif	//	 _WIN32

    protected:
        void InternalCreate() override;
        void InternalDestroy() override;    

    private:
        void OnResize(const System::WindowResizeEvent&);
        void OnKeyDown(const System::KeyEvent&);
    private:
		System::IWindowUniquePtr m_window{ nullptr,  Core::DestroyObject };
        CanvasDescription m_canvas_description;
        HGLRC m_opengl_context;
        int m_shader_version {0};
        int m_opengl_version {0};
        System::ILogger* m_logger {nullptr};
        IVideoDriverUniquePtr m_video_driver {nullptr, DestroyVideoDriver};

		PUNK_OBJECT_DEFAULT_IMPL3(Canvas);
    };
}
PUNK_ENGINE_END

#endif // CONFIG_H

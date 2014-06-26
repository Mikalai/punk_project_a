#ifndef CANVAS_H
#define CANVAS_H

#include <graphics/opengl/module.h>

#include <config.h>
#include <system/window/iwindow.h>
#include "canvas_desciption.h"
#include "icanvas.h"

PUNK_ENGINE_BEGIN
namespace System { class ILogger; }
namespace Graphics {

    class PUNK_ENGINE_LOCAL Canvas : public System::IWindow, public ICanvas {
    public:
        Canvas();
        virtual ~Canvas();		

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	ICanvas
		void Initialize(const CanvasDescription& desc = CanvasDescription()) override;
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
		void InternalCreate() override;
		void InternalDestroy() override;
#ifdef _WIN32
		HWND GetNativeHandle() override;
#elif defined __linux__
        void SetVisualInfo(XVisualInfo* visual) override;
        Window GetNativeHandle() override;
        Display* GetDisplay() override;
#endif

    private:
        void OnResize(const System::WindowResizeEvent&);
        void OnKeyDown(const System::KeyEvent&);
    private:		
        CanvasDescription m_canvas_description;
        System::IWindowUniquePtr m_window{ nullptr,  Core::DestroyObject };
#ifdef WIN32       
        HGLRC m_opengl_context;
#elif defined __linux__
        GLXContext m_context;        
#endif
        int m_shader_version {0};
        int m_opengl_version {0};
        System::ILogger* m_logger {nullptr};
        IVideoDriverUniquePtr m_video_driver {nullptr, Core::DestroyObject};
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		
    };
}
PUNK_ENGINE_END

#endif // CANVAS_H

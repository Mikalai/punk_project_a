#ifndef PUNK_CANVAS_INTERFACE_H
#define PUNK_CANVAS_INTERFACE_H

#include <config.h>
#include <system/window/module.h>
#include <core/iobject.h>
#include <memory>

PUNK_ENGINE_BEGIN
namespace Graphics {
    class CanvasDescription;
    class IVideoDriver;

	static const Core::Guid IID_ICanvas{ "32DD4B5D-3DA5-4738-A740-744077E1B223" };

    class ICanvas : public Core::IObject {
    public:
		virtual void Initialize(const CanvasDescription& desc) = 0;
        virtual void SetFullscreen(bool value) = 0;
        virtual System::IWindow* GetWindow() = 0;
        virtual const CanvasDescription& GetDescription() = 0;
        virtual IVideoDriver* GetVideoDriver() = 0;
        virtual void SwapBuffers() = 0;
    };

	using ICanvasPointer = Core::Pointer < ICanvas > ;    
}
PUNK_ENGINE_END

#endif // PUNK_CANVAS_INTERFACE_H

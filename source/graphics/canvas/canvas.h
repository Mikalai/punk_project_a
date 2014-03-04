#ifndef GPU_COMMON_CONFIG_H
#define GPU_COMMON_CONFIG_H

#ifdef _WIN32
#include <graphics/opengl/module.h>
#endif

#include <config.h>
#include <system/window/win32_window.h>
#include "canvas_desciption.h"
#include "canvas_interface.h"

PUNK_ENGINE_BEGIN
namespace System { class ILogger; }
namespace Graphics {

    class PUNK_ENGINE_LOCAL Canvas : public System::WindowWin, public ICanvas {
    public:
        Canvas(const CanvasDescription& desc = CanvasDescription());        
        void SetFullscreen(bool value) override;

    protected:
        void InternalCreate() override;
        void InternalDestroy() override;    

    private:
        void OnResize(const System::WindowResizeEvent&);
    private:
        CanvasDescription m_canvas_description;
        HGLRC m_opengl_context;
        int m_shader_version = 0;
        int m_opengl_version = 0;
        System::ILogger* m_logger;
    };
}
PUNK_ENGINE_END

#endif // CONFIG_H

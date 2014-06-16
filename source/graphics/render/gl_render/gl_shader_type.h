#ifndef SHADER_TYPE_H
#define SHADER_TYPE_H

#include <string/string.h>
#include <graphics/render/irender_context.h>
#include <graphics/opengl/module.h>
#include <graphics/render/shader_type.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {        
        PUNK_ENGINE_LOCAL const Core::String GetShaderFile(RenderContextType render, ShaderType type);
		PUNK_ENGINE_LOCAL GLenum ConvertShaderTypeToOpenGL(ShaderType type);
    }
}
PUNK_ENGINE_END

#endif // SHADER_TYPE_H

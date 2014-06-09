#include <algorithm>
#include <string/module.h>
#include <graphics/opengl/module.h>
#include <system/module.h>
#include "gl_shader.h"
#include <system/environment.h>
#include <system/filesystem/module.h>
#include <graphics/state/module.h>
#include <graphics/opengl/module.h>
#include <graphics/error/module.h>
#include <graphics/primitives/module.h>

PUNK_ENGINE_BEGIN
namespace Graphics
{
	namespace OpenGL
	{
        static System::ILogger* shader_logger = System::GetDefaultLogger();

		ShaderBase::~ShaderBase()
        {
        }
	}
}
PUNK_ENGINE_END

//#ifndef _H_PUNK_OPENGL_DRIVER_ISHADER
//#define _H_PUNK_OPENGL_DRIVER_ISHADER
//
//#include <memory>
//#include <config.h>
//#include <system/environment.h>
//#include <system/filesystem/module.h>
//#include <graphics/state/module.h>
//#include <graphics/opengl/module.h>
//#include <graphics/error/module.h>
//#include <graphics/primitives/module.h>
//#include <graphics/render/render_context/gl_shader_type.h>
//#include <graphics/render/render_context/gl_render_context/gl_rc_dynamic.h>
//#include "gl_shader_type.h"
//
//PUNK_ENGINE_BEGIN
//namespace Core {
//	class String;
//}
//
//namespace Graphics {
//	class CoreState;
//	namespace OpenGL
//	{
//		class DynamicRenderContext;
//		class IShader
//		{
//		public:
//			virtual void CookFromFile(const Core::String& filename) = 0;
//			virtual void CookFromFileWithHeaders(const Core::String& filename, int count, const char** names) = 0;
//			virtual void CookFromString(const char* filename, unsigned length) = 0;
//			virtual void CookFromStringWithHeaders(const char* data, unsigned length, int count, const char** names) = 0;
//			virtual unsigned GetIndex() const = 0;
//			virtual void Connect(DynamicRenderContext* rc) = 0;
//			virtual void InitUniforms() = 0;
//			virtual void BindParameters(const CoreState&) = 0;
//			virtual int64_t GetRequiredAttributesSet() const = 0;
//		};
//	}
//}
//PUNK_ENGINE_END
//
//#endif

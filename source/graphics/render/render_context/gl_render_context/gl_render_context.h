#ifndef _H_PUNK_OPENGL_DUMMY_RENDER_CONTEXT
#define _H_PUNK_OPENGL_DUMMY_RENDER_CONTEXT

#include <graphics/render/render_context/irender_context.h>
#include <graphics/shaders/gl_shaders/gl_shader_type.h>
#include <graphics/shaders/gl_shaders/gl_shader_types/module.h>
#include <math/vec4.h>
#include <math/mat4.h>

PUNK_ENGINE_BEGIN
namespace Graphics {
    namespace OpenGL {

        class Shader;

        class OpenGLRenderContext : public IRenderContext
		{
		public:
            OpenGLRenderContext(RenderPolicySet policy);
            OpenGLRenderContext(RenderPolicySet policy, ShaderCollection VS, ShaderCollection FS, ShaderCollection GS);
			virtual void Begin() override;
			virtual void End() override;
			virtual void Init() override;
            virtual RenderPolicySet GetPolicy() override;
			virtual ~OpenGLRenderContext();

			bool SetUniformVector4f(const char * name, const float* value);
            bool SetUniformVector4f(const char * name, const Math::vec4& value);
            bool SetUniformVector4f( int index, const float* value );
            bool SetUniformVector4f( int index, const Math::vec4& value );
			bool SetUniformVector3f(const char * name, const float* value );
            bool SetUniformVector3f(const char * name, const Math::vec3& value);
			bool SetUniformVector3f(int index, const float* value);
            bool SetUniformVector3f(int index, const Math::vec3& value);
			bool SetUniformVector2f(const char * name, const float* value );
            bool SetUniformVector2f(const char * name, const Math::vec2& value );
			bool SetUniformVector2f(int index, const float* value );
            bool SetUniformVector2f(int index, const Math::vec2& value );
			bool SetUniformFloat(const char * name, float value);
			bool SetUniformFloat(int index, float value);
			bool SetUniformInt(const char * name, int value);
			bool SetUniformInt(int index, int value);
            bool SetUniformBool(int index, bool value);
			bool SetUniformMatrix2f(const char * name, const float* value);
            bool SetUniformMatrix2f(const char * name, const Math::mat2& value);
			bool SetUniformMatrix2f( int index, const float* value);
            bool SetUniformMatrix2f( int index, const Math::mat2& value);
			bool SetUniformMatrix3f(const char * name, const float* value);
            bool SetUniformMatrix3f(const char * name, const Math::mat3& value);
            bool SetUniformMatrix3f( int index, const float* value);
            bool SetUniformMatrix3f( int index, const Math::mat3& value);
			bool SetUniformMatrix4f(const char * name, const float* value);
            bool SetUniformMatrix4f(const char * name, const Math::mat4& value);
			bool SetUniformMatrix4f( int index, const float* value);
            bool SetUniformMatrix4f( int index, const Math::mat4& value);
			bool SetUniformArrayMatrix4f(int index, int count, const float* value);
            bool SetUniformArrayMatrix4f(int index, int count, const Math::mat4* value);
            bool SetUniformLight(const LightSourceShaderParameters& light, const LightParameters& value);
            bool SetUniformMaterial(const MaterialShaderParameters& material, const Material& value);
			int  GetUniformLocation(const char * name);
            const LightSourceShaderParameters GetUniformLightLocation(const char* name);
            const MaterialShaderParameters GetUniformaMaterialLocation(const char* name);
            const FogShaderParameters GetUniformFogLocation(const char* name);
			void GetUniformVector(const char * name, float* out);
			bool SetTexture(const char * name, int texUnit);
			bool SetTexture(int index, int texUnit);
			bool BindAttributeTo(int index, const char * name);
			bool SetAttribute(const char * name, const float* value);
			bool SetAttribute(int index, const float* value);
			int IndexForAttrName(const char * name);
			void GetAttribute(const char * name, float* out);
			void GetAttribute(int index, float* out);			
			void SetUpOpenGL(const CoreState& state);

		protected:
			Shader* m_vertex_shader;
			Shader* m_fragment_shader;
			Shader* m_geometry_shader;
            RenderPolicySet m_policy{RenderPolicySet::Begin};

			unsigned m_program;
		};

        template<ShaderCollection VS, ShaderCollection FS, ShaderCollection GS> class RenderContextPolicy;
	}
}
PUNK_ENGINE_END

#endif	//	_H_PUNK_OPENGL_DUMMY_RENDER_CONTEXT

#include <sstream>
#include <system/logger/module.h>
#include <system/environment.h>

#include <graphics/texture/module.h>
#include <graphics/render/gl_render/gl_shader_base.h>
#include <graphics/error/module.h>
#include <graphics/opengl/module.h>
#include <graphics/blending/gl_blending.h>
#include "gl_render_context_base.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	namespace OpenGL {

        GlRenderContextBase::GlRenderContextBase(RenderContextType policy)
			: m_program(0)
            , m_policy{policy}
		{
			m_vertex_shader = nullptr;
			m_fragment_shader = nullptr;
			m_geometry_shader = nullptr;
		}

		void GlRenderContextBase::Begin()
		{
			if (!m_initialized)
				Initialize();
			GL_CALL(glUseProgram(m_program));
		}
		
		void GlRenderContextBase::ApplyState(const CoreState& state) {
			SetUpOpenGL(state);
			m_vertex_shader->ApplyState(state);
			m_fragment_shader->ApplyState(state);
			if (m_geometry_shader)
				m_geometry_shader->ApplyState(state);			
		}

		void GlRenderContextBase::End()
		{
			GL_CALL(glUseProgram(0));
		}

		void GlRenderContextBase::SetShaders(ShaderBase *vs, ShaderBase *fs, ShaderBase *gs)
		{
			if ((m_vertex_shader = vs))
				m_vertex_shader->Connect(this);
			if ((m_fragment_shader = fs))
				m_fragment_shader->Connect(this);
			if ((m_geometry_shader = gs))
				m_geometry_shader->Connect(this);
			m_initialized = false;
		}

		void GlRenderContextBase::Initialize()
		{
			if (m_program)
			{
				GL_CALL(glDeleteProgram(m_program));
			}
			GL_CALL(m_program = glCreateProgram());
			try {
				if (m_vertex_shader && m_vertex_shader->GetIndex())
				{
					GL_CALL(glAttachShader(m_program, m_vertex_shader->GetIndex()));
				}
				else
					throw Error::OpenGLException(L"Vertex shader not set");

				if (m_fragment_shader && m_fragment_shader->GetIndex())
				{
					GL_CALL(glAttachShader(m_program, m_fragment_shader->GetIndex()));
				}
				else
					throw Error::OpenGLException(L"Fragment shader not set");

				if (m_geometry_shader && m_geometry_shader->GetIndex())
				{
					GL_CALL(glAttachShader(m_program, m_geometry_shader->GetIndex()));
				}

				GL_CALL(glLinkProgram(m_program));

				GLint status;
				GL_CALL(glGetProgramiv(m_program, GL_LINK_STATUS, &status));
				if (status == GL_TRUE)
				{
					GL_CALL(glValidateProgram(m_program));
					GL_CALL(glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status));
					if (status != GL_TRUE)
						throw Error::OpenGLException(L"Shader program validation failed");
				}
				else
					throw Error::OpenGLException(L"Unable to link shader program");

				if (m_vertex_shader)
					m_vertex_shader->Initialize();
				if (m_fragment_shader)
					m_fragment_shader->Initialize();
				if (m_geometry_shader)
					m_geometry_shader->Initialize();

				m_initialized = true;
			}
			catch (...){
				GL_CALL(glDeleteProgram(m_program));
				m_program = 0;
				throw;
			}
		}		

#define STRICT 0

		bool GlRenderContextBase::SetUniformVector4f(const char * name, const float* value)
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform4fv(index, 1, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformVector4f(const char *name, const Math::vec4 &value)
        {
            return SetUniformVector4f(name, &value[0]);
        }

		bool GlRenderContextBase::SetUniformVector4f( int index, const float* value )
		{
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform4fv(index, 1, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformVector4f(int index, const Math::vec4 &value)
        {
            return SetUniformVector4f(index, &value[0]);
        }

		bool GlRenderContextBase::SetUniformVector3f(const char * name, const float* value )
		{
            GL_CALL(int index = glGetUniformLocation(m_program, name));
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform3fv(index, 1, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformVector3f(const char *name, const Math::vec3 &value)
        {
            return SetUniformVector3f(name, &value[0]);
        }

		bool GlRenderContextBase::SetUniformVector3f(int index, const float* value)
		{
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform3fv(index, 1, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformVector3f(int index, const Math::vec3 &value)
        {
            return SetUniformVector3f(index, &value[0]);
        }

		bool GlRenderContextBase::SetUniformVector2f(const char * name, const float* value )
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform2fv(index, 1, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformVector2f(const char *name, const Math::vec2 &value)
        {
            return SetUniformVector2f(name, &value[0]);
        }

		bool GlRenderContextBase::SetUniformVector2f(int index, const float* value )
		{
			if (index == -1)
            {
#if STRICT == 1
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform2fv(index, 1, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformVector2f(int index, const Math::vec2 &value)
        {
            return SetUniformVector2f(index, &value[0]);
        }

		bool GlRenderContextBase::SetUniformFloat(const char * name, float value)
		{
            GL_CALL(int index = glGetUniformLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1f(index, value));
			return true;
		}

		bool GlRenderContextBase::SetUniformFloat(int index, float value)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1f(index, value));
			return true;
		}

		bool GlRenderContextBase::SetUniformInt(const char * name, int value)
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i(index, value));
			return true;
		}

		bool GlRenderContextBase::SetUniformInt(int index, int value)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i( index, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformBool(int index, bool value)
        {
            if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i( index, (int)value));
            return true;
        }

		bool GlRenderContextBase::SetUniformMatrix2f(const char * name, const float* value)
		{
            GL_CALL(int index = glGetUniformLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed set uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix2fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformMatrix2f(const char *name, const Math::mat2 &value)
        {
            return SetUniformMatrix2f(name, &value[0]);
        }

        bool GlRenderContextBase::SetUniformMatrix2f(int index, const float* value)
		{		
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed set uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix2fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformMatrix2f(int index, const Math::mat2 &value)
        {
            return SetUniformMatrix2f(index, &value[0]);
        }

		bool GlRenderContextBase::SetUniformMatrix3f(const char * name, const float* value)
		{
            GL_CALL(int index = glGetUniformLocation (m_program, name));
            if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix3fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformMatrix3f(const char * name, const Math::mat3& value)
        {
            return SetUniformMatrix3f(name, &value[0]);
        }

		bool GlRenderContextBase::SetUniformMatrix3f( int index, const float* value)
		{		
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed set uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix3fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformMatrix3f(int index, const Math::mat3 &value)
        {
            return SetUniformMatrix3f(index, &value[0]);
        }

		bool GlRenderContextBase::SetUniformMatrix4f(const char * name, const float* value)
		{
            GL_CALL(int index = glGetUniformLocation (m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed set uniform {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix4fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformMatrix4f(const char *name, const Math::mat4 &value)
        {
            return SetUniformMatrix4f(name, &value[0]);
        }

		bool GlRenderContextBase::SetUniformMatrix4f( int index, const float* value)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed set uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix4fv(index, 1, GL_FALSE, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformMatrix4f(int index, const Math::mat4 &value)
        {
            return SetUniformMatrix4f(index, &value[0]);
        }

		bool GlRenderContextBase::SetUniformArrayMatrix4f(int index, int count, const float* value)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(index));
#else
                return false;
#endif
            }
            GL_CALL(glUniformMatrix4fv(index, count, GL_FALSE, value));
			return true;
		}

        bool GlRenderContextBase::SetUniformArrayMatrix4f(int index, int count, const Math::mat4* value)
        {
            return SetUniformArrayMatrix4f(index, count, (float*)value);
        }

        bool GlRenderContextBase::SetUniformLight(const LightSourceShaderParameters &light, const LightParameters &value)
        {
            SetUniformInt(light.enabled, value.IsEnabled());
            if (value.IsEnabled())
            {
                SetUniformVector4f(light.direction, value.GetDirection());
                SetUniformVector4f(light.position, value.GetPosition().data());
                SetUniformVector4f(light.view_direction, value.GetViewDirection());
                SetUniformVector4f(light.view_position, value.GetViewPosition().data());
                SetUniformVector4f(light.diffuse_color, value.GetDiffuseColor());
                SetUniformVector4f(light.ambient_color, value.GetAmbientColor());
                SetUniformFloat(light.attenuation_constant, value.GetLightConstantAttenuation());
                SetUniformFloat(light.attenuation_linear, value.GetLightLinearAttenuation());
                SetUniformFloat(light.attenuation_quadric, value.GetLightQuadricAttenuation());
                SetUniformFloat(light.spot, value.GetSpotExponent());
                SetUniformInt(light.type, (int)value.GetType());
                SetUniformInt(light.attenuation_model, (int)value.GetLightAttenuation());
            }
            return true;
        }

        bool GlRenderContextBase::SetUniformMaterial(const MaterialShaderParameters &material, const Material &value)
        {
            SetUniformVector4f(material.diffuse, value.m_diffuse_color);
            SetUniformVector4f(material.specular, value.m_specular_color);
            SetUniformFloat(material.shininess, value.m_specular_factor);
			return true;
        }

		int GlRenderContextBase::GetUniformLocation(const char * name)
		{
            GL_CALL(GLint res = glGetUniformLocation(m_program, name));
            if (res == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(name));
#else
                return -1;
#endif
            }
			return res;
		}

		void GlRenderContextBase::GetUniformVector(const char * name, float* out)
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed get uniform {0}").arg(name));
#else
                ;
#endif
            }
            GL_CALL(glGetUniformfv(m_program, index, out));
		}

		bool GlRenderContextBase::SetTexture(const char * name, int texUnit)
		{
            GL_CALL(int index = glGetUniformLocation ( m_program, name ));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed set texture {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i(index, texUnit));
			return true;
		}

		bool GlRenderContextBase::SetTexture(int index, int texUnit)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed set texture {0}").arg(texUnit));
#else
                return false;
#endif
            }
            GL_CALL(glUniform1i(index, texUnit));
			return true;
		}

		bool GlRenderContextBase::BindAttributeTo(int index, const char * name)
		{
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed to bind attribute {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glBindAttribLocation(m_program, index, name));
			return true;
		}

		bool GlRenderContextBase::SetAttribute(const char * name, const float* value)
		{
            GL_CALL(int index = glGetAttribLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed to set attribute {0}").arg(name));
#else
                return false;
#endif
            }
            GL_CALL(glVertexAttrib4fv ( index, value ));
			return true;
		}

		bool GlRenderContextBase::SetAttribute(int index, const float* value)
		{
			if (index == -1)
				return false;
            GL_CALL(glVertexAttrib4fv(index, value));
			return true;
		}

		int GlRenderContextBase::IndexForAttrName(const char * name)
		{
            GL_CALL(int index = glGetAttribLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed to get attribute {0}").arg(name));
#else
                return -1;
#endif
            }
            return index;
		}

		void GlRenderContextBase::GetAttribute(const char * name, float* out)
		{
            GL_CALL(int index = glGetAttribLocation(m_program, name));
			if (index == -1)
            {
#if STRICT
                throw System::PunkException(Core::String("Failed to get attribute {0}").arg(name));
#else
                ;
#endif
            }
            GL_CALL(glGetVertexAttribfv ( index, GL_CURRENT_VERTEX_ATTRIB, out));
		}

		void GlRenderContextBase::GetAttribute(int index, float* out)
		{
			if (index == -1)
				return;
            GL_CALL(glGetVertexAttribfv(index, GL_CURRENT_VERTEX_ATTRIB, out));
		}

		GlRenderContextBase::~GlRenderContextBase()
		{
			System::GetDefaultLogger()->Debug("GlRenderContextBase destroyed");
			delete m_vertex_shader;
			m_vertex_shader = nullptr;
			delete m_fragment_shader;
			m_fragment_shader = nullptr;
			delete m_geometry_shader;
			m_geometry_shader = nullptr;

			if (m_program)
			{
                GL_CALL(glDeleteProgram(m_program));
			}
			m_program = 0;
		}

		void GlRenderContextBase::SetUpOpenGL(const CoreState &state)
		{
            GL_CALL(glLineWidth(state.render_state->m_line_width));
            GL_CALL(glPointSize(state.render_state->m_point_size));

			if (state.render_state->m_enable_wireframe)
			{				
                GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			}
			else
			{
                GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			}

			if (state.render_state->m_depth_test)
			{
                GL_CALL(glEnable(GL_DEPTH_TEST));
			}
			else
			{
                GL_CALL(glDisable(GL_DEPTH_TEST));
			}

			if (state.render_state->m_enable_blending)
			{
                GL_CALL(glEnable(GL_BLEND));
				auto src = BlendFunctionToOpenGL(state.render_state->m_blend_src);
				auto dst = BlendFunctionToOpenGL(state.render_state->m_blend_dst);
				auto color = state.render_state->m_blend_color;
                GL_CALL(glBlendFunc(src, dst));
                GL_CALL(glBlendColor(color[0], color[1], color[2], color[3]));
			}
			else
			{
                GL_CALL(glDisable(GL_BLEND));
			}

			BindTextures(state);
		}

		void GlRenderContextBase::BindTextures(const CoreState& state) {
			if (state.render_state->m_enable_texture)
			{
				if (state.texture_state->m_texture_array && state.texture_state->m_texture_array_slot != -1)
				{
					state.texture_state->m_texture_array->Bind(state.texture_state->m_texture_array_slot);
					for (int i = 0; i != 4; ++i)
						if (state.texture_state->m_diffuse_map[i] && state.texture_state->m_diffuse_slot[0] != -1)
							state.texture_state->m_diffuse_map[i]->Bind(state.texture_state->m_diffuse_slot[i]);
					if (state.texture_state->m_height_map && state.texture_state->m_height_map_slot != -1)
						state.texture_state->m_height_map->Bind(state.texture_state->m_height_map_slot);
					if (state.texture_state->m_normal_map && state.texture_state->m_normal_map_slot != -1)
						state.texture_state->m_normal_map->Bind(state.texture_state->m_normal_map_slot);
					if (state.texture_state->m_shadow_map && state.texture_state->m_shadow_map_slot != -1)
						state.texture_state->m_shadow_map->Bind(state.texture_state->m_shadow_map_slot);
					if (state.texture_state->m_text_map && state.texture_state->m_text_map_slot != -1)
						state.texture_state->m_text_map->Bind(state.texture_state->m_text_map_slot);
				}
				else
				{
					for (int i = 0; i != 4; ++i)
						if (state.texture_state->m_diffuse_map[i] && state.texture_state->m_diffuse_slot[0] != -1)
							state.texture_state->m_diffuse_map[i]->Bind(state.texture_state->m_diffuse_slot[i]);
					if (state.texture_state->m_height_map && state.texture_state->m_height_map_slot != -1)
						state.texture_state->m_height_map->Bind(state.texture_state->m_height_map_slot);
					if (state.texture_state->m_normal_map && state.texture_state->m_normal_map_slot != -1)
						state.texture_state->m_normal_map->Bind(state.texture_state->m_normal_map_slot);
					if (state.texture_state->m_shadow_map && state.texture_state->m_shadow_map_slot != -1)
						state.texture_state->m_shadow_map->Bind(state.texture_state->m_shadow_map_slot);
					if (state.texture_state->m_text_map && state.texture_state->m_text_map_slot != -1)
						state.texture_state->m_text_map->Bind(state.texture_state->m_text_map_slot);
				}
			}
		}

        const LightSourceShaderParameters GlRenderContextBase::GetUniformLightLocation(const char* name)
        {
            LightSourceShaderParameters uLight;
            {
                std::stringstream stream;
                stream << name << ".ambient_color";
                uLight.ambient_color = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".attenuation_constant";
                uLight.attenuation_constant = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".attenuation_linear";
                uLight.attenuation_linear = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".attenuation_model";
                uLight.attenuation_model = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".attenuation_quadric";
                uLight.attenuation_quadric = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".diffuse_color";
                uLight.diffuse_color = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".direction";
                uLight.direction = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".position";
                uLight.position = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".view_direction";
                uLight.view_direction = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".view_position";
                uLight.view_position = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".spot";
                uLight.spot = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".type";
                uLight.type = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".enabled";
                uLight.enabled = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".specular_color";
                uLight.specular_color = GetUniformLocation(stream.str().c_str());
            }
            return uLight;
        }

        const MaterialShaderParameters GlRenderContextBase::GetUniformaMaterialLocation(const char* name)
        {
            MaterialShaderParameters material;
            {
                std::stringstream stream;
                stream << name << ".diffuse";
                material.diffuse = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".shininess";
                material.shininess = GetUniformLocation(stream.str().c_str());
            }

            {
                std::stringstream stream;
                stream << name << ".specular";
                material.specular = GetUniformLocation(stream.str().c_str());
            }

            return material;
        }

        const FogShaderParameters GlRenderContextBase::GetUniformFogLocation(const char* name)
        {
            FogShaderParameters fog;
			memset(&fog, 0, sizeof(fog));
            return fog;
        }
	}
}
PUNK_ENGINE_END

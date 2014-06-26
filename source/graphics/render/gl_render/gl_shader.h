#ifndef H_SHADER
#define H_SHADER

#include <system/environment.h>
#include <system/filesystem/folder.h>
#include <graphics/render/render_context_type.h>
#include "gl_shader_base.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	namespace OpenGL {

		struct NoShaderAspect {};

		template<RenderContextType Policy, ShaderType Type> struct ShaderAspect;

		template<ShaderType Type, RenderContextType Policy, typename Aspect = ShaderAspect<Policy, Type> >
		class PUNK_ENGINE_LOCAL Shader : public ShaderBase {
		public:
			
			using CurrentAspect = ShaderAspect < Policy, Type > ;

			Shader() {}
			
			void Initialize() override {
				m_aspect->InitUniforms();
			}

			void ApplyState(const CoreState& state) override {
				m_aspect->BindParameters(state);
			}

			int64_t GetRequiredAttributesSet() const {
				return m_aspect->GetRequiredAttributesSet();
			}

			void Connect(GlRenderContextBase* rc) override {
				m_aspect.reset(new CurrentAspect(rc));
				m_aspect->Cook();
			}

            std::uint32_t GetIndex() const override {
				return m_aspect->GetIndex();
			}

			ShaderType GetType() const override {
				return Type;
			}

		private:
			std::unique_ptr<CurrentAspect> m_aspect;
		};

		template<ShaderType Type, RenderContextType Policy>
		class PUNK_ENGINE_LOCAL Shader<Type, Policy, NoShaderAspect> : public ShaderBase {
		public:

			Shader() {}

			void Initialize() override {
			}

			void ApplyState(const CoreState& state) override {
			}

			int64_t GetRequiredAttributesSet() const {
				return 0;
			}
			
			void Connect(GlRenderContextBase* rc) override {
			}

            std::uint32_t GetIndex() const override {
				return 0;
			}

			ShaderType GetType() const override {
				return Type;
			}
		};

	}
}
PUNK_ENGINE_END

#endif	//	H_SHADER

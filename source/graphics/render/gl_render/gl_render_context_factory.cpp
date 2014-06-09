#ifndef _H_PUNK_OPENGL_SHADER_SOLID_COLOR
#define _H_PUNK_OPENGL_SHADER_SOLID_COLOR

#include <array>
#include <core/ifactory.h>
#include <graphics/render/render_context_type.h>
#include <graphics/render/irender_context_factory.h>
#include "gl_render_context.h"
#include "gl_no_light_solid_color.h"
#include "gl_light_per_fragment_diffuse.h"

PUNK_ENGINE_BEGIN
namespace Graphics {
	namespace OpenGL {

		class GlRenderContextFactory : public IRenderContextFactory {
		public:
			virtual ~GlRenderContextFactory();
			//	IObject
			void QueryInterface(const Core::Guid& type, void** object) override;
			std::uint32_t AddRef() override;
			std::uint32_t Release() override;

			//	IRenderContext
			IRenderContext* GetOrCreateContext(RenderContextType) override;
			void Initialize(IVideoDriver* driver) override;
		private:
			GlRenderContextBase* CreateContext(RenderContextType type);
		private:
			IVideoDriver* m_driver{ nullptr };
			std::array<GlRenderContextBase*, GetIndex(RenderContextType::TotalCount)> m_contexts;
			std::atomic<std::uint32_t> m_ref_count;
		};

		GlRenderContextFactory::~GlRenderContextFactory() {
			for (auto& i : m_contexts) {
				delete i;
				i = nullptr;
			}
		}
		void GlRenderContextFactory::QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IRenderContextFactory });
		}

		std::uint32_t GlRenderContextFactory::AddRef() {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t GlRenderContextFactory::Release() {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		IRenderContext* GlRenderContextFactory::GetOrCreateContext(RenderContextType value) {
			auto result = m_contexts[GetIndex(value)];
			if (result == nullptr)
				result = m_contexts[GetIndex(value)] = CreateContext(value);
			return result;
		}

		GlRenderContextBase* GlRenderContextFactory::CreateContext(RenderContextType value) {
			switch (value)
			{
			case Punk::Engine::Graphics::RenderContextType::NoRender:
				break;
			case Punk::Engine::Graphics::RenderContextType::NoLightSolidColor:
				return new GlRenderContext<RenderContextType::NoLightSolidColor>;
			case Punk::Engine::Graphics::RenderContextType::NoLightSolidColorTextured:
				break;
			case Punk::Engine::Graphics::RenderContextType::NoLightSolidColorSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::NoLightSolidColorTexturedSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::NoLightVertexColor:
				break;
			case Punk::Engine::Graphics::RenderContextType::NoLightVertexColorTextured:
				break;
			case Punk::Engine::Graphics::RenderContextType::NoLightVertexColorSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::NoLightVertexColorTexturedSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuse:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseSpecular:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseSpecularShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseSpecularShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseSpecularSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseSpecularSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingDiffuseSpecularSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuse:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseSpecular:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseSpecularShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseSpecularShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseSpecularSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseSpecularSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::BumpMappingTextureDiffuseSpecularSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuse:
				return new GlRenderContext < RenderContextType::LightPerFragmentDiffuse > ;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseSpecular:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseSpecularShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseSpecularShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseSpecularSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseSpecularSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentDiffuseSpecularSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuse:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseSpecular:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseSpecularShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseSpecularShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseSpecularSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseSpecularSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerFragmentTextureDiffuseSpecularSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuse:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseSpecular:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseSpecularShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseSpecularShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseSpecularSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseSpecularSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexDiffuseSpecularSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuse:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseSpecular:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseSpecularShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseSpecularShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseSpecularSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseSpecularSkinningShadowingSimple:
				break;
			case Punk::Engine::Graphics::RenderContextType::LightPerVertexTextureDiffuseSpecularSkinningShadowingCascade:
				break;
			case Punk::Engine::Graphics::RenderContextType::TextSolidColor:
				break;
			case Punk::Engine::Graphics::RenderContextType::DepthRender:
				break;
			case Punk::Engine::Graphics::RenderContextType::DepthRenderSkinning:
				break;
			case Punk::Engine::Graphics::RenderContextType::TotalCount:
				break;
			default:
				break;
			}
			return nullptr;
		}

		void GlRenderContextFactory::Initialize(IVideoDriver* driver) {
			m_driver = driver;
		}

		PUNK_REGISTER_CREATOR(IID_IRenderContextFactory, Core::CreateInstance<GlRenderContextFactory>);

	}
}
PUNK_ENGINE_END

#endif

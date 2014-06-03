#include <graphics/module.h>
#include "irender_processor.h"

PUNK_ENGINE_BEGIN
namespace LowLevelRender {
	
	class PUNK_ENGINE_LOCAL RenderProcessor : public IRenderProcessor{
	public:
		RenderProcessor();
		virtual ~RenderProcessor();
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;
		void SetSceneManager(SceneModule::ISceneManager* manager) override;
		void Update(float dt) override;

	private:

		void Process(Graphics::IFrame* frame, SceneModule::INode* node);

		template<class T>
		struct LightCache {
			T* m_light;
			Math::vec3 m_position;
			LightCache(T* light, Math::vec3 world_pos)
				: m_light{ light }
				, m_position{ world_pos } {}
		};

		std::vector<LightCache<Attributes::IPointLight>> m_point_lights;
		std::vector<LightCache<Attributes::IDirectionalLight>> m_dir_light;
		std::vector<LightCache<Attributes::ISpotLight*>> m_spot_lights;
		SceneModule::ISceneManager* m_manager{ nullptr };
		Graphics::ICanvas* m_canvas{ nullptr };
		Graphics::IVideoDriver* m_driver{ nullptr };
		Graphics::ILowLevelRender* m_render{ nullptr };
		Graphics::IFrameBuffer* m_frame_buffer{ nullptr };
		Graphics::IFrame* m_frame{ nullptr };	
		std::atomic<std::uint32_t> m_ref_count{ 1 };
	};
}
PUNK_ENGINE_END
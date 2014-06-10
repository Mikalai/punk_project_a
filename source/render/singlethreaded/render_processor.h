#include <graphics/module.h>
#include <attributes/module.h>
#include <math/vec3.h>
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

		template<class T>
		struct CameraCache {
			T* m_camera;
			Math::vec3 m_position;
			Math::vec3 m_direction;

			CameraCache(T* camera, Math::vec3 world_pos, Math::vec3 dir)
				: m_camera{ camera }
				, m_position{ world_pos }
				, m_direction{ dir }
				{}
		};
		
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		SceneModule::ISceneManager* m_manager{ nullptr };
		Graphics::IVideoDriver* m_driver{ nullptr };
		Graphics::ILowLevelRender* m_render{ nullptr };
		Graphics::IFrameBuffer* m_frame_buffer{ nullptr };
		Graphics::IFrame* m_frame{ nullptr };		
		std::vector<LightCache<Attributes::IPointLight>> m_point_lights;
		std::vector<LightCache<Attributes::IDirectionalLight>> m_dir_light;
		std::vector<LightCache<Attributes::ISpotLight>> m_spot_lights;
		CameraCache<Attributes::IPerspectiveCamera> m_perspective_camera{ nullptr, { 0, 0, 0 }, { 0, 0, -1 } };

	public:
		static Graphics::ICanvasUniquePtr Canvas;
	};
}
PUNK_ENGINE_END
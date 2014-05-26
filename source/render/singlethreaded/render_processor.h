#include "irender_processor.h"

PUNK_ENGINE_BEGIN
namespace Render {
	
	class PUNK_ENGINE_LOCAL RenderProcessor : public IRenderProcessor{
	public:
		void QueryInterface(const Core::Guid& type, void** object) override;
		void SetSceneManager(SceneModule::ISceneManager* manager) override;
		void Update(int dt) override;

	private:
		SceneModule::ISceneManager* m_manager{ nullptr };

		PUNK_OBJECT_DEFAULT_IMPL(RenderProcessor);
	};
}
PUNK_ENGINE_END
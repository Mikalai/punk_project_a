#include <core/ifactory.h>
#include "render_processor.h"

PUNK_ENGINE_BEGIN
namespace Render {

	void RenderProcessor::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { IID_IRenderProcessor, Core::IID_IObject });
	}

	void RenderProcessor::SetSceneManager(SceneModule::ISceneManager* manager) {
		m_manager = manager;
	}

	void RenderProcessor::Update(int dt) {
		if (!m_manager)
			return;
	}

	PUNK_REGISTER_CREATOR(IID_IRenderProcessor, Core::CreateInstance<RenderProcessor>);
}
PUNK_ENGINE_END
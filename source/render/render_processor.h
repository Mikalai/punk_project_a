#ifndef _H_PUNK_RENDER_PROCESSOR
#define _H_PUNK_RENDER_PROCESSOR

#include <config.h>
#include <scene/graph_processor_base.h>
#include <graphics/module.h>
#include "render_commands.h"

PUNK_ENGINE_BEGIN
namespace Scene {
	class ISceneGraph;
	class INode;
}
namespace Graphics {

}
namespace Render {

	class PUNK_ENGINE_API RenderProcessor : public Scene::GraphProcessorBase {
	public:
		RenderProcessor();
		virtual ~RenderProcessor();
		void SetGraph(Scene::ISceneGraph* graph) override;
		const Core::String GetName() const override;
		bool Process(Scene::INode* node, bool (RenderProcessor::*func)(Scene::INode*));

		bool Delete(Scene::INode* node);
		bool OnNodeAdded(Scene::INode* child);
		bool OnNodeRemoved(Scene::INode* child);

		void AddChild(Scene::INode* parent, Scene::INode* child);
		void RemoveChild(Scene::INode* parent, Scene::INode* child);
		void ChildAdded(Scene::INode* parent, Scene::INode* child);
		void ChildRemoved(Scene::INode* parent, Scene::INode* child);

		void Show();
		void Hide();

	protected:
		void OnStartProcessing() override;
		void OnInternalUpdate(int dt) override;
		void OnInternalUpdate(Scene::CommandBase* task) override;
		void OnPreUpdate(Scene::CommandBase* command) override;
		void OnPostUpdate(Scene::CommandBase* command) override;
		void OnWaitProcessingComplete() override;

	private:
		void OnShow();
		void OnHide();

		void OnSetNewGraph(CmdSetNewScene* cmd);

		Scene::INodeUniquePtr CreateRenderNode(const Core::String& name);

	private:
		Graphics::ICanvasUniquePtr m_canvas{ nullptr, Graphics::DestroyCanvas };
		Scene::INode* m_camera_node{ nullptr };
	};

}
PUNK_ENGINE_END

#endif	//	_H_PUNK_RENDER_PROCESSOR
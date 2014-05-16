#ifndef _H_RENDER_COMMANDS
#define _H_RENDER_COMMANDS

#include <graphics/module.h>
#include <scene/command.h>

PUNK_ENGINE_BEGIN
namespace Scene {
	class ISceneGraph;
}

namespace Render {
	static const int RenderDomain = 2;

	enum class RenderCommands {
		SetNewScene, 
		Show,
		CookMesh,
		MeshCooked
	};

	struct CmdSetNewScene : public Scene::Command < RenderDomain, (int)RenderCommands::SetNewScene > {
		Scene::ISceneGraph* graph{ nullptr };
	};

	struct CmdShow : public Scene::Command < RenderDomain, (int)RenderCommands::Show > {
		bool visible{ true };
	};

	struct CmdCookMesh : public Scene::Command < RenderDomain, (int)RenderCommands::CookMesh > {
		Scene::INode* node_with_data{ nullptr };
	};

	struct CmdMeshCooked : public Scene::Command < RenderDomain, (int)RenderCommands::MeshCooked > {
		Scene::INode* node_with_data{ nullptr };
		Graphics::IRenderable* renderable{ nullptr };
	};
}
PUNK_ENGINE_END

#endif	//	_H_RENDER_COMMANDS
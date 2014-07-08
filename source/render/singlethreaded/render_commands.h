#ifndef _H_RENDER_COMMANDS
#define _H_RENDER_COMMANDS

#include <graphics/module.h>
#include <scene/command.h>

PUNK_ENGINE_BEGIN

namespace LowLevelRender {
	static const int RenderDomain = 2;

	enum class RenderCommands {
		SetNewScene, 
		Show,
		CookMesh,
		MeshCooked
	};

	struct CmdSetNewScene : public SceneModule::Command < RenderDomain, (int)RenderCommands::SetNewScene > {
		SceneModule::ISceneGraph* graph{ nullptr };
	};

	struct CmdShow : public SceneModule::Command < RenderDomain, (int)RenderCommands::Show > {
		bool visible{ true };
	};

	struct CmdCookMesh : public SceneModule::Command < RenderDomain, (int)RenderCommands::CookMesh > {
		Core::Pointer<SceneModule::INode> node_with_data{ nullptr };
	};

	struct CmdMeshCooked : public SceneModule::Command < RenderDomain, (int)RenderCommands::MeshCooked > {
		Core::Pointer<SceneModule::INode> node_with_data{ nullptr };
		Graphics::IRenderable* renderable{ nullptr };
	};
}
PUNK_ENGINE_END

#endif	//	_H_RENDER_COMMANDS
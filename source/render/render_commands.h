#ifndef _H_RENDER_COMMANDS
#define _H_RENDER_COMMANDS

#include <scene/command.h>

PUNK_ENGINE_BEGIN
namespace Scene {
	class ISceneGraph;
}

namespace Render {
	static const int RenderDomain = 2;

	enum class RenderCommands {
		SetNewScene, 
		Show
	};

	struct CmdSetNewScene : public Scene::Command < RenderDomain, (int)RenderCommands::SetNewScene > {
		Scene::ISceneGraph* graph{ nullptr };
	};

	struct CmdShow : public Scene::Command < RenderDomain, (int)RenderCommands::Show > {
		bool visible{ true };
	};
}
PUNK_ENGINE_END

#endif	//	_H_RENDER_COMMANDS
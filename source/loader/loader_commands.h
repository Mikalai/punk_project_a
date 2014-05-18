#ifndef _H_LOADER_COMMANDS
#define _H_LOADER_COMMANDS

#include <config.h>
#include <scene/command.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN
namespace Scene {
	class INode;
	class ISceneGraph;
}
namespace Core {
	class IObject;
}
namespace Loader {

	static const int LoaderDomain = 1;	

	enum class LoaderCommands {
		Add,
		Remove,
		NodeAdded,
		NodeRemoved,
		AddLoadedObject,
		SetNewGraph,
		LoadFile
	};



	struct CmdAdd : public Scene::Command<LoaderDomain, (int)LoaderCommands::Add> {
		Scene::INode* parent{ nullptr };
		Scene::INode* child{ nullptr };
	};

	struct CmdRemove : public Scene::Command<LoaderDomain, (int)LoaderCommands::Remove> {
		Scene::INode* parent{ nullptr };
		Scene::INode* child{ nullptr };
	};

	struct CmdNodeAdded : public Scene::Command<LoaderDomain, (int)LoaderCommands::NodeAdded> {
		Scene::INode* parent{ nullptr };
		Scene::INode* new_node{ nullptr };
	};

	struct CmdNodeRemoved : public Scene::Command<LoaderDomain, (int)LoaderCommands::NodeRemoved> {
		Scene::INode* parent{ nullptr };
		Scene::INode* old_node{ nullptr };
	};

	struct CmdAddLoadedObject : public Scene::Command<LoaderDomain, (int)LoaderCommands::AddLoadedObject> {
		Scene::INode* node{ nullptr };
		Core::IObject* object{ nullptr };
	};

	struct CmdSetGraph : public Scene::Command<LoaderDomain, (int)LoaderCommands::SetNewGraph> {
		Scene::ISceneGraph* new_graph{ nullptr };
	};	
	
	struct CmdLoadFile : public Scene::Command<LoaderDomain, (int)LoaderCommands::LoadFile> {
		Scene::INode* node;
		Core::String filename;
	};
}
PUNK_ENGINE_END
#endif	//	_H_LOADER_COMMANDS

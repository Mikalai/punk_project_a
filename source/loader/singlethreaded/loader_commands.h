//#ifndef _H_LOADER_COMMANDS
//#define _H_LOADER_COMMANDS
//
//#include <config.h>
//#include <scene/module.h>
//#include <string/module.h>
//
//PUNK_ENGINE_BEGIN
//namespace SceneModule {
//	class INode;
//	class IScene;
//}
//namespace Core {
//	class IObject;
//}
//namespace IoModule {
//
//	static const int LoaderDomain = 1;	
//
//	enum class LoaderCommands {
//		Add,
//		Remove,
//		NodeAdded,
//		NodeRemoved,
//		AddLoadedObject,
//		SetNewGraph,
//		LoadFile
//	};
//
//
//
//	struct CmdAdd : public SceneModule::Command<LoaderDomain, (int)LoaderCommands::Add> {
//		Core::Pointer<SceneModule::INode> parent{ nullptr };
//		Core::Pointer<SceneModule::INode> child{ nullptr };
//	};
//
//	struct CmdRemove : public SceneModule::Command<LoaderDomain, (int)LoaderCommands::Remove> {
//		Core::Pointer<SceneModule::INode> parent{ nullptr };
//		Core::Pointer<SceneModule::INode> child{ nullptr };
//	};
//
//	struct CmdNodeAdded : public SceneModule::Command<LoaderDomain, (int)LoaderCommands::NodeAdded> {
//		Core::Pointer<SceneModule::INode> parent{ nullptr };
//		Core::Pointer<SceneModule::INode> new_node{ nullptr };
//	};
//
//	struct CmdNodeRemoved : public SceneModule::Command<LoaderDomain, (int)LoaderCommands::NodeRemoved> {
//		Core::Pointer<SceneModule::INode> parent{ nullptr };
//		Core::Pointer<SceneModule::INode> old_node{ nullptr };
//	};
//
//	struct CmdAddLoadedObject : public SceneModule::Command<LoaderDomain, (int)LoaderCommands::AddLoadedObject> {
//		Core::Pointer<SceneModule::INode> node{ nullptr };
//		Core::IObject* object{ nullptr };
//	};
//
//	struct CmdSetGraph : public SceneModule::Command<LoaderDomain, (int)LoaderCommands::SetNewGraph> {
//		SceneModule::IScene* new_graph{ nullptr };
//	};	
//	
//	struct CmdLoadFile : public SceneModule::Command<LoaderDomain, (int)LoaderCommands::LoadFile> {
//		Core::Pointer<SceneModule::INode> node;
//		Core::String filename;
//	};
//}
//PUNK_ENGINE_END
//#endif	//	_H_LOADER_COMMANDS

//#ifndef _H_LOADER_TASKS
//#define _H_LOADER_TASKS
//
//#include <config.h>
//
//PUNK_ENGINE_BEGIN
//namespace IoModule {
//	enum class LoaderTasks {
//		Load,
//		SetNewGraph
//	};
//
//	struct SetNewGraphTask {
//		SceneModule::ISceneGraph* new_graph;
//	};
//
//	struct LoadFileTask {
//		SceneModule::INode* node;
//		wchar_t filename[MAX_PATH];
//	};
//
//	//
//	//  Task is anything that should be processed in the internal thread of the processor
//	//
//	struct LoaderTask {
//		LoaderTasks task;
//		union {
//			LoadFileTask load_file;
//			SetNewGraphTask set_graph;
//		};
//	};
//}
//PUNK_ENGINE_END

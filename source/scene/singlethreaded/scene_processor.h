//#ifndef SCENE_PROCESSOR_H
//#define SCENE_PROCESSOR_H
//
//#include <deque>
//#include <vector>
//#include <system/concurrency/module.h>
//#include "iscene_graph.h"
//#include "igraph_processor.h"
//#include "iscene_processor.h"
//
//PUNK_ENGINE_BEGIN
//namespace SceneModule {
//
//    enum class Code {
//        None,
//        SetNewScene,
//        Update,
//        DestroyScene,
//        Terminate
//    };
//
//    struct SetNewSceneCommand {
//        wchar_t filename[MAX_PATH];
//		wchar_t datapath[MAX_PATH];
//    };
//
//    struct UpdateCommand {
//        int m_dt;
//    };
//
//    struct DestroySceneCommand {
//
//    };
//
//    struct TerminateCommand {
//
//    };
//
//    struct Command {
//        Code code;
//        union {
//            SetNewSceneCommand set_new_scene;
//            UpdateCommand update;
//            DestroySceneCommand destroy_scene;
//            TerminateCommand terminate;
//        };
//    };
//
//    class SceneProcessor : public ISceneProcessor
//    {
//    public:
//        SceneProcessor();
//        virtual ~SceneProcessor();
//		
//		virtual void BeginPreProcessSync() = 0;
//		virtual void PreProcess() = 0;
//		virtual void EndPreProcessSync() = 0;
//		virtual void BeginPostProcessSync() = 0;
//		virtual void PostProcess() = 0;
//		virtual void EndPostProcessSync() = 0;
//		virtual void InternalProcess() = 0;
//		virtual void SendAsyncCommand(CommandBase* cmd) = 0;
//		virtual void SendSyncCommand(CommandBase* cmd) = 0;
//		virtual void WaitComplete() = 0;
//		virtual void Terminate() = 0;		
//
//    private:                
//		Core::String m_scene_file;
//		Core::String m_data_path;
//        std::vector<IGraphProcessor*> m_proc;
//        ISceneGraphUniquePtr m_scene_graph{nullptr, Core::DestroyObject};
//        System::Thread m_thread;
//        std::deque<Command> m_commands;
//        System::Monitor m_lock;
//    };
//
//}
//PUNK_ENGINE_END
//
//
//#endif // SCENE_PROCESSOR_H
